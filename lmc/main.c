#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

uint16_t mailbox[100];
int PC = 0;
uint16_t accumulator;
uint16_t INBOX;
uint16_t OUTBOX;
int run = 1;
bool negativeFlag = false;

int load(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		return -1;
	}
	int i = 0;
	while (fscanf(file, "%d", &mailbox[i]) == 1)
	{
		i++;
	}
	fclose(file);
	return 0;
}

int main()
{
	load("program.txt");
	while (run)
	{
		uint16_t instruction = mailbox[PC];
		PC++;
		uint16_t temp_instruction = instruction;
		uint16_t address_1 = temp_instruction % 10;
		temp_instruction = temp_instruction / 10;
		uint16_t address_2 = temp_instruction % 10;
		uint16_t address = address_1 + address_2 * 10;
		temp_instruction = temp_instruction / 10;
		uint16_t opcode = temp_instruction;
		switch (opcode)
		{
			case 1:
				if (accumulator + mailbox[address] < 999) 
				{
					accumulator += mailbox[address];
				}
				negativeFlag = false;
				break;
			case 2:
				if (accumulator - mailbox[address] >= 0) 
				{
					accumulator -= mailbox[address];
				}
				else
				{
					negativeFlag = true;
				}
				break;
			case 3:
				mailbox[address] = accumulator;
				negativeFlag = false;
				break;
			case 5:
				accumulator = mailbox[address];
				negativeFlag = false;
				break;
			case 6:
				PC = address;
				negativeFlag = false;
				break;
			case 7:
				if (negativeFlag == true)
				{
					PC = address;
				}
				negativeFlag = false;
				break;
			case 8:
				if (negativeFlag == false)
				{
					PC = address;
				}
				negativeFlag = false;
				break;
			case 9:
				if (instruction == 901)
				{
					printf("Enter INBOX: ");
					scanf("%d", &INBOX);
					accumulator = INBOX;
				}
				else if (instruction == 902)
				{
					OUTBOX = accumulator;
					printf("OUTBOX: %d\n", OUTBOX);
				}
				negativeFlag = false;
				break;
			case 0:
				run = 0;
				break;
			default:
				printf("Invalid command\n");
				break;
		}
	}
	return 0;
}