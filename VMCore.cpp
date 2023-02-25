
#include "VMCore.hpp"


// Настройки виртуальной машины

static const int MAXMEM = 5;
// Массив памяти, который состоит из элементов типа int
static int stack[MAXMEM];
// Указатель на положение данных в стеке, сейчас стек не инициализирован
static int sp = -1;
static bool VM = true; // true - машина запущена, false - машина не работает
static int ip = 0; // Указатель на инструкцию (мнемонику)


// Проверка стека на пустоту
// Функция вернет TRUE (1), если стек пуст,
// и FALSE (0), если данные есть
int empty_sp() {
  return sp == -1 ? 1 : 0;
}

// Проверка стека на заполненность
// Функция вернет TRUE (1), если стек полон,
// и FALSE (0), если место еще есть
int full_sp() {
  return sp == MAXMEM ? 1 : 0;
}

void VMDecoder(int instr) {
    switch (instr) {
        case PUSH: {
            // Проверяем, есть ли место в памяти
            if (full_sp()) {
                printf("Memory is full\n");
                break;
            }
            // Перемещаемся в свободную ячейку памяти
            sp++;
            // В массиве кода берем следующее за мнемоникой PUSH значение
            // и кладем его в ячейку памяти
            stack[sp] = code[++ip];
            break;
        }
        case POP: {
            // Проверка памяти на пустоту
            if (empty_sp()) {
                printf("Memory is empty\n");
                break;
            }
            // Берем значение с верхушки стека
            int pop_value = stack[sp--];
            // и выводим его
            printf("Result: %d \n", pop_value);
            break;
        }
        case ADD: {
            // Берем два верхних значения стека
            int a = stack[sp--];
            int b = stack[sp--];
            sp++;
            // Складываем их и кладем результат на стек
            stack[sp] = b + a;
            // Выводим сообщение
            printf("ADD->");
            break;
        }
        case SUB: {
            // Берем два верхних значения стека
            int a = stack[sp--];
            int b = stack[sp--];
            sp++;
            // Вычитаем их и кладем результат на стек
            stack[sp] = a - b;
            // Выводим сообщение
            printf("SUB->");
            break;
        }
        case DIV: {
            // Берем два верхних значения стека
            int a = stack[sp--];
            int b = stack[sp--];
            sp++;
            // Делим их и кладем результат на стек
            stack[sp] = a / b;
            // Выводим сообщение
            printf("DIV->");
            break;
        }
        case MUL: {
            // Берем два верхних значения стека
            int a = stack[sp--];
            int b = stack[sp--];
            sp++;
            // Перемножаем их и кладем результат на стек
            stack[sp] = a * b;
            // Выводим сообщение
            printf("DIV->");
            break;
        }
        case RAM: {
            // Это простой цикл вывода всех значений массива
            int x = sp;
            for (; x >= 0; --x) {
                printf("RAM[%u]: %u\n", x, stack[x]);
            }
            break;
        }
        case TEST: {
            break;
        }
        case PRINT: {
            printf("PRINT Stack[%u]: %u\n", sp, stack[sp]);
            break;
        }
//         case ENTER: {
//             printf("ENTER NEW VAR: 201527\n");
//             sp++;
//             int pass = 201527;
//             memcpy(&stack[sp], &pass, 5);
//             break;
//         }
        case EXIT: {
            // Установка глобальной переменной в FALSE,
            // чтобы прервать работу VM
            VM = false;
            printf("Exit VM\n");
            break;
        }
            
    }
}


void VMStart() {
    while (VM) { // Переменная, которая контролирует работу VM
        VMDecoder(code[ip]);
        ip++;
      }
}
