#include "CpuMarcio.hpp"
#include <iostream>
#include <stdio.h>
#include <cmath>
#pragma once

using namespace std;

void CpuMarcio::receiveDigit(Digit digit){
  if(this->isFirstOperand == 1){
    if(this->digitsOperand1Count < 8){
      this->digitsOperand1[this->digitsOperand1Count] = digit;
      this->digitsOperand1Count += 1;
      this->display->addDigit(digit);
      }
  }
  else{
    if(this->digitsOperand2Count < 8){
      this->digitsOperand2[this->digitsOperand2Count] = digit;
      this->digitsOperand2Count += 1;
      this->display->addDigit(digit);
    }
  }
}

void CpuMarcio::proccessOperation(){
  switch(this->operation){
    case ADDITION:
      this->memory+=this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
      break;
    case SUBTRACTION:
      this->memory-=this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
      break;
    case MULTIPLICATION:
      this->memory*=this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
      break;
    case DIVISION:
      this->memory/=this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
      break;
    case PERCENTAGE:
      this->memory= (this->memory *this->getOperand(this->digitsOperand2, this->digitsOperand2Count))/100;
      break;
    case SQUARE_ROOT:
      this->memory= sqrt(this->memory);
    case NOOP:
        printf("NOOP\n");
        break;
    case EQUAL:
        printf("equal\n");
        break;
    default:
      printf("Default \n");
      break;
  }
}

float CpuMarcio::getOperand(Digit * digits, int count){
  float result = 0;
  int multiplier = 10;
  int i = count - 1;
  for(i; i > count - 1 - this->indexDecimalSaparator; i--){
    float number = (float)(digits[i]);
    result +=  number / multiplier;
    multiplier*=10;
  }
  multiplier = 1;
  for(i; i >= 0; i--){
    float number = (float)(digits[i]);
    result +=  number * multiplier;
    multiplier*=10;
  }
  return result;
}

void CpuMarcio::setDigits(){
  int count = 0;
  float aux = this->memory;
  while(aux > 1){
    aux = aux /10;
    count++;
  }
  // printf("Aux em cima: %f\n", aux);
  aux = this->memory;
  int j = count;
  // printf("Count: %d\n", count);
  int divider = pow(10, j-1);
  for(int i = 0; i < count; i++){
    // printf("Aux: %f\n", aux);
    int number = aux/divider;
    aux-=divider * number;
    // printf("Number: %d\n", number);
    switch(number){
      case 0:
        this->display->addDigit(ZERO);
        break;
      case 1:
        this->display->addDigit(ONE);
        break;
      case 2:
        this->display->addDigit(TWO);
        break;
      case 3:
        this->display->addDigit(THREE);
        break;
      case 4:
        this->display->addDigit(FOUR);
        break;
      case 5:
        this->display->addDigit(FIVE);
        break;
      case 6:
        this->display->addDigit(SIX);
        break;
      case 7:
        this->display->addDigit(SEVEN);
        break;
      case 8:
        this->display->addDigit(EIGHT);
        break;
      case 9:
        this->display->addDigit(NINE);
        break;
    }
    j--;
    divider/=10;
  }
}


// ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, PERCENTUAL, SQUARE, EQUAL, NOOP
void CpuMarcio::receiveOperation(Operation operation){
  if(this->isFirstOperand == 1){
      this->memory=this->getOperand(this->digitsOperand1, this->digitsOperand1Count);
    this->isFirstOperand = 0;
    this->operation = operation; 
  }
  else{
    if(operation == EQUAL){
      this->proccessOperation();
      this->display->clear();
      this->setDigits();
      printf("%f\n", this->memory);
    }
    else{
      this->proccessOperation();
      this->operation = operation;
      // this->isFirstOperand = 0;
    }
  }
  this->digitsOperand1Count = 0;
  this->digitsOperand2Count = 0;
  this->display->clear();
  // Guardo a operação, mas antes verificar se já existe uma definida e já exisite um operand2
  
}

void CpuMarcio::receiveControl(Control control){
  switch(control){
    case ON_CLEAR_ERROR: this->display->clear(); break;
    case DECIMAL_SEPARATOR:
      this->indexDecimalSaparator = this->digitsOperand1Count > 0 ? this->digitsOperand1Count : this->digitsOperand2Count;
      this->display->addDigit(NO_DIGIT, true);
      break;
    case MEMORY_SUBTRACTION:
      if(this->digitsOperand1Count > 0){
        this->memory -= this->getOperand(this->digitsOperand1, this->digitsOperand1Count);
        this->digitsOperand1Count = 0;
      }
      else{
        this->memory -= this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
        this->digitsOperand2Count = 0;
      }
      this->display->clear();
      break;
    case MEMORY_ADDITION:
      if(this->digitsOperand1Count > 0){
        this->memory += this->getOperand(this->digitsOperand1, this->digitsOperand1Count);
        this->digitsOperand1Count = 0;
      }
      else{
        this->memory += this->getOperand(this->digitsOperand2, this->digitsOperand2Count);
        this->digitsOperand2Count = 0;
      }
      this->display->clear();
      break;
  }
}

void CpuMarcio::setDisplay(Display& display){
  this->display = &display;
}
