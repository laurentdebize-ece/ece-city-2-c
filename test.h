//
// Created by maell on 07/11/2022.
//

#ifndef ECE_CITY_2_C_TEST_H
#define ECE_CITY_2_C_TEST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct route
{
    int x;
    int y;

} route;

typedef struct reseauEau
{
    int x;
    int y;

} reseauEau;
typedef struct reseauElectricite
{
    int x;
    int y;

} reseauElectricite;

typedef struct habitation
{
    int x;
    int y;

} habitation;

typedef struct caserne
{
    int x;
    int y;

} caserne;

typedef struct usineEau
{
    int x;
    int y;

} usineEau;

typedef struct usineElectricite
{
    int x;
    int y;

} usineElectricite;

typedef struct chemin
{
    route* route;
    reseauEau* reseauEau;
    reseauElectricite* reseauElectricite;

} chemin;

typedef struct bat
{
     habitation* habitation;

} bat;

typedef struct usines
{
    caserne* caserne;
    usineEau* usineEau;
    usineElectricite* usineElectricite;

} usines;


typedef struct InfoConstruction
{
    chemin* chemin;
    bat* bat;
    usines* usines;

} InfoConstruction;


#endif //ECE_CITY_2_C_TEST_H
