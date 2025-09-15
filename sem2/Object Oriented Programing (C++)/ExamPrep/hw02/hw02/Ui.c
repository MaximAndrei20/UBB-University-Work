#include "Ui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Product.h"
#include "Service.h"

UI* createUI(Service* service)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (ui == NULL)
		return NULL;
	ui->service = service;

	return ui;
}

void destroyUI(UI* ui)
{
	if (ui == NULL)
		return;
	free(ui);
}

void startUI(UI* ui)
{
	while (1)
	{
		printMenu();

		int command = 0;
		scanf("%d", &command);
		switch (command)
		{
		case 0:
			return;
		case 1:
		{	//get the name, category, quantity and expiration date
			char name[50], category[50], expirationDate[50];
			int quantity;
			printf("Name: ");
			scanf("%s", name);
			printf("Category: ");
			scanf("%s", category);
			printf("Quantity: ");
			scanf("%d", &quantity);
			printf("Expiration date: ");
			scanf("%s", expirationDate);

			//add the product
			addProduct(ui->service, name, category, quantity, expirationDate);
			break;
		}
		case 2:
		{//identify each product by name and category then delete it
			char name[50], category[50];
			printf("Name: ");
			scanf("%s", name);
			printf("Category: ");
			scanf("%s", category);
			deleteProductUi(ui, name, category);
			break;
		}
		case 3:
		{
			char name[50], category[50];
			printf("Name of product: ");
			scanf("%s", name);
			printf("Category of product: ");
			scanf("%s", category);
			updateProductUi(ui->service, name, category);
			break;
		}
		case 4:
		{
			char str[50];
			printf("String: ");
			getchar();
			fgets(str, 50, stdin);
			listProductsByString(ui->service, str);
			break;
		}
		case 5:
			displayProductsByCategoryAndExpiration(ui);
			break;
		case 6:
			if (undo(ui->service) == 0)
				printf("Undo successful\n");
			else
				printf("Nothing to undo\n");
			break;
		case 7:
			if (redo(ui->service) == 0)
				printf("Redo successful\n");
			else
				printf("Nothing to redo\n");
			break;
		default:
			printf("Invalid command\n");
			break;
		}
	}
}

int updateProductUi(Service* s, char* name, char* category)
{
	char newName[50], newCategory[50], newExpirationDate[50];
	int newQuantity;
	printf("New name: ");
	scanf("%s", newName);
	printf("New category: ");
	scanf("%s", newCategory);
	printf("New quantity: ");
	scanf("%d", &newQuantity);
	printf("New expiration date: ");
	scanf("%s", newExpirationDate);

	int pos = findElement(s->repo, name, category);
	if (pos == -1)
	{
		printf("Product not found\n");
		return 1;
	}
	
	Product* p = s->repo->da->elems[pos];
	updateProduct(s, p, newName, newCategory, newQuantity, newExpirationDate);
}

int deleteProductUi(UI* ui, char* name, char* category)
{
	deleteProduct(ui->service, name, category);
}

// Comparison function for sorting products by quantity
void listProductsByString(Service* s, char* str)
{
	// Remove the newline character from the input string
	str[strcspn(str, "\n")] = '\0';

	if (str[0] == '\0') // Check if the string is empty
		printf("\nAll products:\n");
	else
		printf("\nAll products that contain '%s' in their name:\n", str);

	int size;
	Product** products = getSortedProductsByString(s, str, &size);
	if (products == NULL) {
		fprintf(stderr, "Failed to retrieve products\n");
		return;
	}

	// Print the sorted products
	for (int i = 0; i < size; i++) {
		Product* p = products[i];
		printf("name: %s | category: %s | quantity: %d | expiration date: %s\n",
			getName(p), getCategory(p), getQuantity(p), getExpirationDate(p));
	}

	// Free the temporary array
	free(products);
	printf("\n");
}

void displayProductsByCategoryAndExpiration(UI* ui) {
	getchar();
	char category[50];
	int days;
	printf("Category (leave empty for all): ");

	fgets(category, sizeof(category), stdin);
	category[strcspn(category, "\n")] = 0; // Remove the newline character

	printf("Number of days: ");
	if (scanf("%d", &days) != 1) {
		printf("Invalid input\n");
		while (getchar() != '\n'); // Clear the input buffer
		return;
	}
	getchar(); // Consume the newline character left by scanf

	int size;
	Product** products = getProductsByCategoryAndExpiration(ui->service, category, days, &size);
	if (products == NULL) {
		fprintf(stderr, "Failed to retrieve products\n");
		return;
	}

	printf("Products in category '%s' expiring in the next %d days (or already expired):\n", category, days);
	for (int i = 0; i < size; i++) {
		Product* p = products[i];
		printf("name: %s | category: %s | quantity: %d | expiration date: %s\n",
			getName(p), getCategory(p), getQuantity(p), getExpirationDate(p));
	}

	free(products);
}

void printMenu()
{
	printf("1. Add product\n");
	printf("2. Delete product\n");
	printf("3. Update product\n");
	printf("4. List all products by string\n");
	printf("5. Display all products whose expiration date is close\n");
	printf("6. Undo\n");
	printf("7. Redo\n");
	printf("0. Exit\n");
}

