#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

curl_off_t pdltotal = -1;
curl_off_t pdlnow = -1;

int progress_callback(void *clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow)
{
	if (dltotal == pdltotal && dlnow == pdlnow)
	{
		return 0;
	}

	pdlnow = dlnow;
	pdltotal = dltotal;

	char *empty = "____________________";
	char *filled = "####################";

	if (dltotal == 0)
	{
		printf("Progress: %s  0%%; %ld / %ld\n", empty, dlnow, dltotal);
		return 0;
	}

	int percentage = (int)(dlnow / dltotal * 100);
	int pb_size_l = (int)(percentage / 5);
	int pb_size_r = (int)(20 - percentage / 5);
	char *pb_l = calloc(pb_size_l, sizeof(char));
	char *pb_r = calloc(pb_size_r, sizeof(char));
	strncpy(pb_l, filled, pb_size_l);
	strncpy(pb_r, empty + pb_size_l, pb_size_r);

	// printf("%d, %d\n", pb_size_l, pb_size_r);

	printf("\nProgress: %s%s  %d%%; %ld / %ld \n", pb_l, pb_r, percentage, dlnow, dltotal);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("URL argument is required and should be the only argument.");
		return 0;
	}

	CURL *curl = curl_easy_init();
	if (curl)
	{
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
		curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progress_callback);

		res = curl_easy_perform(curl);
		// if (res != 0)
		// {
		// 	printf("%s\n", curl_easy_strerror(res));
		// }
		// else
		// {
		// 	printf("%u\n", res);
		// }

		curl_easy_cleanup(curl);
	}
	return 0;
}
