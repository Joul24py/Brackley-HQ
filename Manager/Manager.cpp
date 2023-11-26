/*#include <iostream>
#include <cmath>
#include <vector>

class BuddyAllocator
{
    public:
        BuddyAllocator(int totalSize);
        ~BuddyAllocator();

        void* allocate(int size);
        void deallocate(void* ptr);

        void display();
        
    private:
        struct Block
        {
            int size;
            bool free;
        };

        int totalSize;
        int levels;
        std::vector<std::vector<Block>> memory;

        int findLevel(int size);
        void split(int level, int index);
        void merge(int level, int index);
};

BuddyAllocator::BuddyAllocator(int totalSize) : totalSize(totalSize)
{
    levels = static_cast<int>(std::log2(totalSize) + 1); // Sospecho que esta línea puede traerme ciertos problemas en el caso: el logaritmo sale entero
    printf("\n\ntotalSize = %d\n", totalSize);
    printf("El logaritmo antes de castearlo a entero = %.4f\n", (std::log2(totalSize) + 1));
    printf("levels = %d\n\n", levels);
    memory.resize(levels);

    for (int i = 0; i < levels; ++i)
    {
        int blockSize = totalSize / (1 << i);
        int blockCount = totalSize / blockSize;

        memory[i].resize(blockCount);
        for (int j = 0; j < blockCount; ++j)
        {
            memory[i][j].size = blockSize;
            memory[i][j].free = true;
        }
    }
}

BuddyAllocator::~BuddyAllocator()
{
    // Deallocate all memory before destroying the allocator
    for (int i = 0; i < levels; ++i)
    {
        for (int j = 0; j < memory[i].size(); ++j)
        {
            // Solo desasignar bloques ocupados para evitar errores
            if (!memory[i][j].free)
            {
                deallocate(static_cast<void*>(&memory[i][j]));
            }
        }
    }
}

void* BuddyAllocator::allocate(int size)
{
    int level = findLevel(size);

    for (int i = level; i < levels; ++i)
    {
        for (int j = 0; j < memory[i].size(); ++j)
        {
            if (memory[i][j].free)
            {
                // Split blocks until the desired size is reached
                while (memory[i][j].size > size)
                {
                    split(i, j);
                }

                memory[i][j].free = false;
                return static_cast<void*>(&memory[i][j]);
            }
        }
    }

    // Unable to allocate memory
    return nullptr;
}

void BuddyAllocator::deallocate(void* ptr)
{
    Block* block = static_cast<Block*>(ptr);
    int level = findLevel(block->size);
    int index = static_cast<int>(block - &memory[level][0]);

    memory[level][index].free = true;

    // Merge blocks until reaching the top level or finding a non-free buddy
    while (level > 0 && memory[level][index].free)
    {
        int buddyIndex = (index % 2 == 0) ? (index + 1) : (index - 1);
        if (!memory[level][buddyIndex].free)
        {
            break;
        }

        merge(level, index);
        index /= 2;
        --level;
    }
}

void BuddyAllocator::split(int level, int index)
{
    memory[level][index].size /= 2;
    memory[level - 1][2 * index].size = memory[level][index].size;
    memory[level - 1][2 * index + 1].size = memory[level][index].size;
}

void BuddyAllocator::merge(int level, int index)
{
    int buddyIndex = (index % 2 == 0) ? (index + 1) : (index - 1);
    memory[level][index / 2].size *= 2;
    memory[level][index / 2].free = true;
}

int BuddyAllocator::findLevel(int size)
{
    return levels - static_cast<int>(std::log2(totalSize / size));
}

void BuddyAllocator::display()
{
    for (int i = 0; i < levels; ++i)
    {
        std::cout << "Level " << i << ": ";
        for (int j = 0; j < memory[i].size(); ++j)
        {
            std::cout << "[" << (memory[i][j].free ? 'F' : 'U') << "]";
        }
        std::cout << std::endl;
    }
}

int main()
{
    BuddyAllocator allocator(64);

    // Allocate memory
    void* block1 = allocator.allocate(8);
    void* block2 = allocator.allocate(16);
    void* block3 = allocator.allocate(32);

    // Display the state of the memory after allocations
    allocator.display();

    // Deallocate memory
    allocator.deallocate(block2);

    // Display the state of the memory after deallocation
    allocator.display();

    return 0;
}*/

#include <iostream>
#include <conio.h>
#include <windows.h>

int main() {
    char key;

    for (;;) {
        // Tu código dentro del ciclo aquí
        std::cout << "Hola Mundo" << std::endl;

        // Verificar si una tecla está presionada
        if (_kbhit()) {
            // Obtener la tecla presionada
            key = _getch();

            // Verificar si la tecla es 'A'
            if (key == 'A' || key == 'a') {
                std::cout << "La tecla 'A' fue presionada." << std::endl;
                //break;  // Puedes salir del bucle si se presiona 'A'
                key = '0';
            }
        }

        // Agregar un pequeño retraso para no consumir demasiado CPU
        // Puedes ajustar el valor según sea necesario
        Sleep(100);
    }

    return 0;
}
