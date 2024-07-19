#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Element
{
    int x;
    int y;
    int value;
    Element *next;
};

Element *dodaj_element(Element *head, int x, int y, int value)
{

    Element *nowy = new Element{x, y, value, nullptr};
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

Element *sumuj_macierze(Element *A, Element *B)
{
    Element *C = nullptr;
    while (A && B)
    {
        if (A->x == B->x && A->y == B->y)
        {
            C = dodaj_element(C, A->x, A->y, A->value + B->value);
            A = A->next;
            B = B->next;
        }
        else if (A->x < B->x || (A->x == B->x && A->y < B->y))
        {
            C = dodaj_element(C, A->x, A->y, A->value);
            A = A->next;
        }
        else
        {
            C = dodaj_element(C, B->x, B->y, B->value);
            B = B->next;
        }
    }
    while (A)
    {
        C = dodaj_element(C, A->x, A->y, A->value);
        A = A->next;
    }
    while (B)
    {
        C = dodaj_element(C, B->x, B->y, B->value);
        B = B->next;
    }
    return C;
}

Element *mnoz_macierze(Element *A, Element *B, int n)
{
    Element *C = nullptr;
    for (Element *a = A; a != nullptr; a = a->next)
    {
        for (Element *b = B; b != nullptr; b = b->next)
        {
            if (a->y == b->x)
            {
                Element *temp = C;
                bool found = false;
                while (temp)
                {
                    if (temp->x == a->x && temp->y == b->y)
                    {
                        temp->value += a->value * b->value;
                        found = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!found)
                {
                    C = dodaj_element(C, a->x, b->y, a->value * b->value);
                }
            }
        }
    }
    return C;
}

void wypisz_liste(Element *head)
{
    while (head)
    {
        cout << "[" << head->x << ", " << head->y << ", " << head->value << "] ";
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

    Element *A = nullptr;
    Element *B = nullptr;

    const int n = 5;         // Rozmiar macierzy (n x n)
    const int maxValue = 30; // Maksymalna wartosc elementu macierzy
    const float prawdopodobienstwo = 1.6; // dzielnik RAND_MAX
    int ilosc_zer = 0;

    // macierz A
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int value;
            if (rand() > RAND_MAX / prawdopodobienstwo)
                value = rand() % (maxValue + 1);
            else
            {
                value = 0;
                ilosc_zer++;
            }

            A = dodaj_element(A, i, j, value);
        }
    }

    cout << endl << "Ilosc zerowych elementow macierzy A: " << ilosc_zer << endl << endl;

    ilosc_zer = 0;

    //macierz B
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int value;
            if (rand() > RAND_MAX / prawdopodobienstwo)
                value = rand() % (maxValue + 1);
            else
            {
                value = 0;
                ilosc_zer++;
            }

            B = dodaj_element(B, i, j, value);
        }
    }

    cout << endl << "Ilosc zerowych elementow macierzy B: " << ilosc_zer << endl << endl;


    cout << endl << "Macierz A: ";
    wypisz_liste(A);

    cout << endl << "Macierz B: ";
    wypisz_liste(B);

    Element *suma = sumuj_macierze(A, B);
    cout << endl << "Suma macierzy: ";
    wypisz_liste(suma);

    Element *iloczyn = mnoz_macierze(A, B, n);
    cout << endl << "Iloczyn macierzy: ";
    wypisz_liste(iloczyn);

    zwolnij_liste(A);
    zwolnij_liste(B);
    zwolnij_liste(suma);
    zwolnij_liste(iloczyn);

    system("pause");

    return 0;
}
