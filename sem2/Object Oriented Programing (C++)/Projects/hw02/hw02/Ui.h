#pragma once
#include "Service.h"


typedef struct {
	Service* service;
}UI;

UI* createUI(Service* service);
void destroyUI(UI* ui);
void startUI(UI* ui);
void printMenu();
void listProductsByString(Service* s, char* str);
int compareProductsByQuantity(const void* a, const void* b);
int deleteProductUi(Service* s, char* name, char* category);
int updateProductUi(Service* s, char* name, char* category);
void displayProductsByCategoryAndExpiration(UI* ui);