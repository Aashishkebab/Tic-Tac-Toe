#pragma once
#ifndef COMPUTER_H
#define COMPUTER_H
char computerLetter;
struct Board;

char ChooseComputerCharacter(char userLetter);
void PlayComputer(Board &board);
#endif