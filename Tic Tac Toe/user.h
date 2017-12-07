#pragma once
#ifndef USERSTUFF_H
#define USERSTUFF_H
char userLetter;
struct Board;

bool PlayGame();
char ChooseYourCharacter();
void PlayUser(Board &board);
#endif