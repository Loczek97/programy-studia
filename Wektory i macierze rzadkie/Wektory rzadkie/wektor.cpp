#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Element
{
    int index;
    int value;
    Element *next;
};

Element *dodaj_element(Element *head, int index, int value)
{
    Element *nowy = new Element{index, value, nullptr};
    if (!head)
    {
        return nowy;
    }
    Element *temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = nowy;
    return head;
}

Element *sumuj_wektory(Element *x, Element *y)
{
    Element *wynik = nullptr;
    while (x && y)
    {
        if (x->index == y->index)
        {
            wynik = dodaj_element(wynik, x->index, x->value + y->value);
            x = x->next;
            y = y->next;
        }
        else if (x->index < y->index)
        {
            wynik = dodaj_element(wynik, x->index, x->value);
            x = x->next;
        }
        else
        {
            wynik = dodaj_element(wynik, y->index, y->value);
            y = y->next;
        }
    }
    while (x)
    {
        wynik = dodaj_element(wynik, x->index, x->value);
        x = x->next;
    }
    while (y)
    {
        wynik = dodaj_element(wynik, y->index, y->value);
        y = y->next;
    }
    return wynik;
}

int iloczyn_skalarny(Element *x, Element *y)
{
    int iloczyn = 0;
    while (x && y)
    {
        if (x->index == y->index)
        {
            iloczyn += x->value * y->value;
            x = x->next;
            y = y->next;
        }
        else if (x->index < y->index)
        {
            x = x->next;
        }
        else
        {
            y = y->next;
        }
    }
    return iloczyn;
}

void wypisz_liste(Element *head)
{
    while (head)
    {
        cout << "[" << head->index << ", " << head->value << "] ";
        head = head->next;
    }
    cout << endl;
}

void zwolnij_liste(Element *head)
{
    while (head)
    {
        Element *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    srand(time(0));

    Element *x = nullptr;
    Element *y = nullptr;

    const int n = 30;                     // Dlugosc wektora
    const int maxValue = 20;              // Maksymalna wartosc elementu wektora
    const float prawdopodobienstwo = 1.3; // Prawdopodobienstwo wystapienia zera (dzielnik RAND_MAX)
    int ilosc_zer = 0;

    // Losowe inicjowanie wektora x
    for (int i = 0; i < n; ++i)
    {
        int value;
        if (rand() > RAND_MAX / prawdopodobienstwo)
            value = rand() % (maxValue + 1);
        else
        {
            value = 0;
            ilosc_zer++;
        }

        x = dodaj_element(x, i, value);
    }

    cout << endl << "Ilosc zerowych elementow wektora x: " << ilosc_zer << endl;

    ilosc_zer = 0;
    for (int i = 0; i < n; ++i)
    {
        int value;
        if (rand() > RAND_MAX / prawdopodobienstwo)
            value = rand() % (maxValue + 1);
        else
        {
            value = 0;
            ilosc_zer++;
        }

        y = dodaj_element(y, i, value);
    }

    cout << endl << "Ilosc zerowych elementow wektora y: " << ilosc_zer << endl << endl;



    cout << endl << "Wektor x: ";
    wypisz_liste(x);

    cout << endl << "Wektor y: ";
    wypisz_liste(y);

    Element *suma = sumuj_wektory(x, y);
    cout << endl << "Suma wektorow: ";
    wypisz_liste(suma);

    int iloczyn = iloczyn_skalarny(x, y);
    cout << endl << "Iloczyn skalarny: " << iloczyn << endl;

    zwolnij_liste(x);
    zwolnij_liste(y);
    zwolnij_liste(suma);

    system("pause");

    return 0;
}
