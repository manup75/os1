#include <stdio.h>
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
void updateLRU(int* lru, int numFrames, int accessedFrame) {
for (int i = 0; i < numFrames; i++) {
if (lru[i] < lru[accessedFrame]) {
lru[i]++;
}
}
lru[accessedFrame] = 0;
}
void LRU(int* pages, int numPages) {
int memory[MAX_PAGES] = { -1 };
int lru[MAX_PAGES] = { 0 };
int hits = 0, misses = 0;
printf("Referenced String: ");
for (int i = 0; i < numPages; i++) {
printf("%d ", pages[i]);
}
printf("\n");
printf("LRU Page Replacement:\n");
for (int i = 0; i < numPages; i++) {
int currentPage = pages[i];
if (isInMemory(currentPage, memory, MAX_PAGES)) {
hits++;
int accessedFrame = -1;
for (int j = 0; j < MAX_PAGES; j++) {
if (memory[j] == currentPage) {
accessedFrame = j;
break;
}
}
updateLRU(lru, MAX_PAGES, accessedFrame);
} else {
misses++;
int replaceIndex = 0;
for (int j = 1; j < MAX_PAGES; j++) {
if (lru[j] > lru[replaceIndex]) {
replaceIndex = j;
}
}
memory[replaceIndex] = currentPage;
updateLRU(lru, MAX_PAGES, replaceIndex);
}
displayMemory(memory, MAX_PAGES);
}
printf("Hits: %d\n", hits);
printf("Misses: %d\n", misses);
printf("Page Faults: %d\n", misses);
}
int main() {
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

// int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 6};
// int numPages = sizeof(pages) / sizeof(pages[0]);
LRU(pages, numPages);
return 0;
}
