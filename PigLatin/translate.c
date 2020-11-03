#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isVowel (char c) {
	if (c == 'a' || c == 'i' || c == 'e' || c == 'u' || c == 'o' || c == 'y' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return 1;
	else return 0;
}

char* word_to_pig_latin(const char *word) {
	int cap = 0;
	if (word[0] <= 90) cap = 1;

	size_t firstVowelPos = 0;
	
	while (1) {
		char cur = word[firstVowelPos]; 
		if (cur == 0 || isVowel(cur) == 1) break;
		firstVowelPos++;
	}

	char* output = calloc(strlen(word) + (!firstVowelPos ? 4 : 3), sizeof(char));

	int pos = 0;
	for (size_t i = firstVowelPos; i < strlen(word) + firstVowelPos; i++) {
		output[pos] = tolower(word[i%strlen(word)]);	
		pos++;
	}

	if (firstVowelPos == 0) sprintf(output, "%sw", output);
	if (cap == 1) output[0] -= 32;
	sprintf(output, "%say", output);
	
	return output;
}

void test_pig_latin() {
    const char *cases[][2] = {
        { "exit", "exitway" },
        { "Yellow", "Ellowyay" },
        { "scram", "amscray" },
        { "blue", "ueblay" },
        { "Type", "Ypetay" },
        { "igloo", "iglooway" },
        { "Float", "Oatflay" },
        { "bandanda",  "andandabay" },
        { "Apple", "Appleway" },
        
        // feel free to add more cases above this line,
        // but leave the { NULL, NULL } line intact.
        { NULL, NULL }
    };
    
    size_t i = 0;
    int failed_cases = 0, passed_casses = 0;
    while(1) {
        const char *original = cases[i][0];
        const char *expected_latin = cases[i][1];
        
        if(!original || !expected_latin) break;
        
        char *actual_latin = word_to_pig_latin(original);
        
        if(!actual_latin || strcmp(expected_latin, actual_latin) != 0) {
            printf("Test case failed: expected '%s' -> '%s', but got '%s'\n", original, expected_latin, actual_latin);
            failed_cases++;
        }
        else {
			printf("Test case passed: expected '%s' -> '%s'\n", original, actual_latin);
            passed_casses++;
        }
        free(actual_latin);
        i++;
    }
    printf("%d/%d cases passed\n", passed_casses, failed_cases + passed_casses);
}

int main() {
    test_pig_latin();
    
    return 0;
}
