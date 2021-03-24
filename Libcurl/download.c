#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct memory
{
	char *response;
	size_t size;
} memory;

curl_off_t pdltotal = -1;
curl_off_t pdlnow = -1;

void display_progress_bar(int percentage, long num, long den)
{
	char *empty = "                    ";
	char *filled = "####################";

	int pb_size_l = (int)(percentage / 5);
	int pb_size_r = 20 - pb_size_l;
	char *pb_l = calloc(pb_size_l, sizeof(char));
	char *pb_r = calloc(pb_size_r, sizeof(char));
	strncpy(pb_l, filled, pb_size_l);
	strncpy(pb_r, empty, pb_size_r);

	// This fprintf prints with a makeshift progressbar
	// fprintf(stderr, "Progress: %s%s  %d%%; %ld / %ld \n", pb_l, pb_r, percentage, num, den);

	// Use this fprintf instead if weird characters pop up in progressbar
	fprintf(stderr, "Progress: %d%%; %ld / %ld \n", percentage, num, den);
}

int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	if ((dlnow != 0 && dltotal == 0) || (dltotal == pdltotal && dlnow == pdlnow))
	{
		return 0;
	}

	display_progress_bar(dltotal == 0 ? 0 : (int)((float)dlnow / (float)dltotal * 100.0), dlnow, dltotal);

	pdlnow = dlnow;
	pdltotal = dltotal;

	if (dltotal == 0)
		return 0;

	// fprintf(stderr, "%ld / %ld = %f\n", dlnow, dltotal, (dlnow / dltotal));

	return 0;
}

static size_t cb(void *data, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct memory *mem = (struct memory *)userp;

	char *ptr = realloc(mem->response, mem->size + realsize + 1);
	if (ptr == NULL)
		return 0; /* out of memory! */

	mem->response = ptr;
	memcpy(&(mem->response[mem->size]), data, realsize);
	mem->size += realsize;
	mem->response[mem->size] = 0;

	return realsize;
}

char *download_url(const char *url, size_t *len)
{
	CURL *curl = curl_easy_init();
	if (curl)
	{
		CURLcode res;
		memory chunk;

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);
		if (res != 0)
		{
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
		len = &chunk.size;
		return chunk.response;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("URL argument is required and should be the only argument.");
		return 0;
	}

	size_t len = 0;

	char *response = download_url(argv[1], &len);

	printf("%s", response);

	return 0;
}
