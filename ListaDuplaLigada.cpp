#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include "Celula.h"
#include "ListaDuplaLigada.h"

using namespace std;

ListaDuplaLigada::ListaDuplaLigada() {
	head = NULL;
	tail = NULL;
	qtdCelulas = 0;
}

bool ListaDuplaLigada::vazia() {
	return head == NULL;
}

int ListaDuplaLigada::tamanho() {
	return qtdCelulas;
}

char ListaDuplaLigada::primeiro() {
    if (head != NULL) return head->getInfo();
	return -1;
}

char ListaDuplaLigada::ultimo() {
    if (tail != NULL) return tail->getInfo();
	return -1;
}

void ListaDuplaLigada::insereInicio(char i) {
	Celula * c = new Celula(i);
	if(head != NULL) head->setAnt(c);
	c->setProx(head);
	c->setAnt(NULL);
	head = c;
	if (tail == NULL) tail = c;
	qtdCelulas++;
}

void ListaDuplaLigada::insereFinal(char n) {
	if(head == NULL) return this->insereInicio(n);
	Celula * c = new Celula(n);
	tail->setProx(c);
	c->setAnt(tail);
	tail = c;
	qtdCelulas++;
}

int ListaDuplaLigada::insereEmN(char n, int pos) {
	if (pos < 1) return -1;

	if (pos > qtdCelulas + 1) return -1;

	if (pos == 1) {
		insereInicio(n);
		return 1;
	}
	if (pos == qtdCelulas + 1){
		insereFinal(n);
		return pos;
	}

	Celula * c = new Celula(n), * cursor;
	int i;
	if(pos <= qtdCelulas / 2){
		cursor = head;
		for (i = 1; i < pos; i++) cursor = cursor->getProx();
	} else{
		cursor = tail;
		for (i = qtdCelulas; i > pos; i--) cursor = cursor->getAnt();	
	}
	c->setProx(cursor);
	c->setAnt(cursor->getAnt());
	cursor->getAnt()->setProx(c);
	cursor->setAnt(c);	
	qtdCelulas++;
	return pos;
}

int ListaDuplaLigada::insereAposN(char n, int pos) {
	return this->insereEmN(n, pos + 1);
}

int ListaDuplaLigada::insereAntesN(char n, int pos) {
	return this->insereEmN(n, pos - 1);
}

char ListaDuplaLigada::removeInicio(){
	if(head == NULL) return -1;
	int n = head->getInfo();
	if(head->getProx() == NULL){
		head = NULL;
		tail = NULL;
	} else{
		head = head->getProx();
		head->setAnt(NULL);
	}
	qtdCelulas--;
	return n;
}

char ListaDuplaLigada::removeFinal(){
	if(head == NULL) return -1;
	int n = tail->getInfo();
	if(head->getProx() == NULL) {
		n = head->getInfo();
		head = NULL;
		tail = NULL;
	} else{
		tail = tail->getAnt();
		tail->setProx(NULL);
	}
	qtdCelulas--;
	return n;
}

char ListaDuplaLigada::removeEmN(int pos) {
	if(head == NULL) return -1;
	
	if (pos < 1) return -1;

	if (pos > qtdCelulas + 1) return -1;

	if (pos == 1) return this->removeInicio();

	if (pos == qtdCelulas) return this->removeFinal();
	int i, n;
	Celula * cursor, *aux;
	if(pos <= qtdCelulas / 2){
		cursor = head;
		for (i = 0; i < pos-2; i++) cursor = cursor->getProx();
		n = cursor->getProx()->getInfo();
		aux = cursor->getProx()->getProx();
		aux->setAnt(cursor);
		cursor->setProx(aux);
	} else{
		cursor = tail;
		for (i = qtdCelulas; i > pos + 1; i--) cursor = cursor->getAnt();	
		n = cursor->getAnt()->getInfo();
		aux = cursor->getAnt()->getAnt();
		aux->setProx(cursor);
		cursor->setAnt(aux);
	}

	qtdCelulas--;
	return n;
}

char ListaDuplaLigada::removeAposN(int pos) {
	return this->removeEmN(pos + 1);
}

char ListaDuplaLigada::removeAntesN(int pos) {
	return this->removeEmN(pos - 1);
}