#include "Service.h"
#include "Repository.h"
#include "Product.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "tests.h"


void test_createRepository() {
    Repository* repo = createRepository();
    assert(repo != NULL);
    assert(repo->da != NULL);
    assert(repo->da->size == 0);
    destroyRepository(repo);
}

void test_addElement() {
    Repository* repo = createRepository();
    Product* p = createProduct("Milk", "Dairy", 10, "20.03.2025");
    addElement(repo, p);
    assert(repo->da->size == 1);
    destroyRepository(repo);
}

void test_deleteElement() {
    Repository* repo = createRepository();
    Product* p = createProduct("Milk", "Dairy", 10, "20.03.2025");
    addElement(repo, p);
    int res = deleteElement(repo, "Milk", "Dairy");
    assert(res == 0);
    assert(repo->da->size == 0);
    destroyRepository(repo);
}

void test_findElement() {
    Repository* repo = createRepository();
    Product* p = createProduct("Milk", "Dairy", 10, "20.03.2025");
    addElement(repo, p);
    int pos = findElement(repo, "Milk", "Dairy");
    assert(pos == 0);
    destroyRepository(repo);
}

void test_setQuantityToPos() {
    Repository* repo = createRepository();
    Product* p = createProduct("Milk", "Dairy", 10, "20.03.2025");
    addElement(repo, p);
    setQuantityToPos(repo, 20, 0);
    assert(getQuantityOfPos(repo, 0) == 20);
    destroyRepository(repo);
}

void test_addProduct() {
    Repository* repo = createRepository();
    Service* service = createService(repo);
    addProduct(service, "Milk", "Dairy", 10, "20.03.2025");
    assert(repo->da->size == 1);
    destroyService(service);
    destroyRepository(repo);
}

void test_deleteProduct() {
    Repository* repo = createRepository();
    Service* service = createService(repo);
    addProduct(service, "Milk", "Dairy", 10, "20.03.2025");
    deleteProduct(service, "Milk", "Dairy");
    assert(repo->da->size == 0);
    destroyService(service);
    destroyRepository(repo);
}

void test_updateProduct() {
    Repository* repo = createRepository();
    Service* service = createService(repo);
    addProduct(service, "Milk", "Dairy", 10, "20.03.2025");
    Product* p = repo->da->elems[0];
    updateProduct(service, p, "Milk", "Dairy", 20, "25.03.2025");
    assert(getQuantity(p) == 20);
    assert(strcmp(getExpirationDate(p), "25.03.2025") == 0);
    destroyService(service);
    destroyRepository(repo);
}

void test_undo_redo() {
    Repository* repo = createRepository();
    Service* service = createService(repo);
    addProduct(service, "Milk", "Dairy", 10, "20.03.2025");
    addProduct(service, "Cheese", "Dairy", 5, "21.03.2025");
    assert(repo->da->size == 2);
    undo(service);
    assert(repo->da->size == 1);
    redo(service);
    assert(repo->da->size == 2);
    destroyService(service);
    destroyRepository(repo);
}

void testFunctionalities()
{
    test_createRepository();
    test_addElement();
    test_deleteElement();
    test_findElement();
    test_setQuantityToPos();
    test_addProduct();
    test_deleteProduct();
    test_updateProduct();
    test_undo_redo();
}
