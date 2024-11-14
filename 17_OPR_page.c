#include <stdio.h>
#include <limits.h>
#define MAX_PAGES 3
int isInMemory(int page, int* memory, int numFrames) {
for (int i = 0; i < numFrames; i++) {
if (memory[i] == page) {
return 1; // Page is in memory
}
}
return 0; // Page is not in memory
}
void displayMemory(int* memory, int numFrames) {
printf("Memory: ");
for (int i = 0; i < numFrames; i++) {
printf("%d ", memory[i]);
}
printf("\n");
}
int findOptimal(int* pages, int start, int numPages, int* memory, int numFrames) {
int farthest = -1;
int farthestIndex = -1;
for (int i = 0; i < numFrames; i++) {
int currentPage = memory[i];
int j;
for (j = start; j < numPages; j++) {
if (pages[j] == currentPage) {
if (j > farthest) {
farthest = j;
farthestIndex = i;
}
break;
}
}
if (j == numPages) {
return i; // If a page will not be referenced in the future, replace it
}
}
if (farthestIndex == -1) {
return 0; // Default case: replace the first page if no other page is farthest
}
return farthestIndex;
}
void OPT(int* pages, int numPages) {
int memory[MAX_PAGES] = { -1 };
int hits = 0, misses = 0;
printf("Referenced String: ");
for (int i = 0; i < numPages; i++) {
printf("%d ", pages[i]);
}
printf("\n");
printf("OPT Page Replacement:\n");
for (int i = 0; i < numPages; i++) {
int currentPage = pages[i];
if (isInMemory(currentPage, memory, MAX_PAGES)) {
hits++;
} else {
misses++;
int replaceIndex = findOptimal(pages, i + 1, numPages, memory,
MAX_PAGES);
memory[replaceIndex] = currentPage;
}
displayMemory(memory, MAX_PAGES);
}
printf("Hits: %d\n", hits);
printf("Misses: %d\n", misses);
printf("Page Faults: %d\n", misses);
}
int main() {

// int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 6};
// int numPages = sizeof(pages) / sizeof(pages[0]);

int numPages;

    // Get the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];

    // Get the page references from the user
    printf("Enter the page references:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

OPT(pages, numPages);
return 0;
}
