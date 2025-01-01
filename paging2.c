#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_PAGES 20

int main() {
    int memorySize, pageSize, noOfProcesses, totalPages, remainingPages;
    int pagesRequired[MAX_PROCESSES], frameNo[MAX_PROCESSES][MAX_PAGES];

    // Input memory size and page size
    printf("Enter the memory size: ");
    scanf("%d", &memorySize);
    printf("Enter the page size: ");
    scanf("%d", &pageSize);

    totalPages = memorySize / pageSize;
    printf("Number of pages available: %d\n", totalPages);

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &noOfProcesses);
    
    remainingPages = totalPages;

    // Input pages required for each process
    for (int i = 0; i < noOfProcesses; i++) {
        printf("Enter the number of pages required for process %d: ", i + 1);
        scanf("%d", &pagesRequired[i]);

        if (pagesRequired[i] > remainingPages) {
            printf("Memory is full. Cannot allocate more pages.\n");
            break;
        }

        remainingPages -= pagesRequired[i];

        // Input page table (frame numbers) for each process
        printf("Enter the page table (frame numbers) for process %d:\n", i + 1);
        for (int j = 0; j < pagesRequired[i]; j++) {
            scanf("%d", &frameNo[i][j]);
        }
    }

    // Logical to physical address conversion
    int processNum, pageNum, offset;
    printf("Enter logical address (process number, page number, offset): ");
    scanf("%d %d %d", &processNum, &pageNum, &offset);

    // Validate input
    if (processNum < 1 || processNum > noOfProcesses || 
        pageNum < 0 || pageNum >= pagesRequired[processNum - 1] || 
        offset < 0 || offset >= pageSize) {
        
        printf("Invalid input.\n");
    } else {
        // Calculate physical address
        int physicalAddress = frameNo[processNum - 1][pageNum] * pageSize + offset;
        printf("The physical address is: %d\n", physicalAddress);
    }

    return 0;
}
