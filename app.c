#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fbrp/reference.h"
#include "fbrp/fbrp.h"
#include "biblec/main.h"
#include "biblec/biblec.h"

struct Translation loadedTranslations[10];

// Simple function to print strings with text break
void printBreak(char *string, int breakAt) {
	for (int c = 0; string[c] != '\0'; c++) {
		putchar(string[c]);
		if (c > breakAt && string[c] == ' ') {
			putchar('\n');
			breakAt *= 2;
		}
	}
}

void debugPrint(struct Reference *ref) {
	printf("Book: %s\n", ref->book);

	for (int c = 0; c < ref->chapterLength; c++) {
		printf("Chapter: %d-%d\n", ref->chapter[c].r[0], ref->chapter[c].r[1]);
	}

	for (int c = 0; c < ref->verseLength; c++) {
		printf("Verse: %d-%d\n", ref->verse[c].r[0], ref->verse[c].r[1]);
	}
}


int main() {
	printf("%s\n", "@ Heb12Lite");

	int tryFile = 0;
	parseIndexFile(
		&tryFile,
		&loadedTranslations[0],
		"bibles/web.i",
		"bibles/web.t"
	);

	if (tryFile) {
		printf("%s", "! Index loading failure");
		return 0;
	} else {
		printf("%s", "@ WEB Bible Loaded");
	}

	while (1) {
		printf("\n: ");
		char input[50];
		fgets(input, 50, stdin);

		if (input[0] == '?') {
			printf("\n%s\n", "@ Type a reference to see the verses");
			continue;
		} else if (input[0] == 'x') {
			return 0;
		}


		int *tryRef;
		struct Reference ref = parseReference(tryRef, input);

		int verses = ref.verseLength;
		if (verses == 0 && ref.chapterLength == 1) {verses = 1;}

		for (int r = 0; r < verses; r++) {
			int verseStart = 1;
			int verseEnd = 0;
			if (ref.verseLength != 0) {
				verseStart = ref.verse[r].r[0];
				verseEnd = ref.verse[r].r[1];
			}

			int tryReader;
			struct Reader reader = reader_new(
				&tryReader,
				&loadedTranslations[0],
				ref.book,
				ref.chapter[0].r[0],
				verseStart,
				verseEnd
			);

			if (tryReader) {
				printf("Verse error = %d", tryReader);
				return 0;
			}

			while (1) {
				if (reader_next(&reader)) {break;}
				putchar('\n');
				printf("%d. ", verseStart + reader.linesRead - 1);
				printBreak(reader.result, 70);
				putchar('\n');
			}

			fclose(reader.file);
		}
	}
}
