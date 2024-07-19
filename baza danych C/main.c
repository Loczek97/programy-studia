#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct Film
{
    unsigned int id;
    char nazwa[50];
    int rokProdukcji;
    char rezyser[50];
};

void menu(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc, int *jestZapisane);

void wczytajBaze(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc, int *jestZapisane);

void zapiszBaze(struct Film **bazaDanych, int liczbaRekordow, int *jestZapisane);

void dodajRekord(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc);

void usunRekord(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc);

void znajdzFilm(struct Film *bazaDanych, int liczbaRekordow);
void wypiszFilm(const struct Film *film);

void edytujRekord(struct Film *bazaDanych, int *liczbaRekordow);

void wypiszBaze(struct Film *bazaDanych, int liczbaRekordow);

void sortujRekordy(struct Film *bazaDanych, int liczbaRekordow);
int porownajId(const void *a, const void *b);
int porownajNazwa(const void *a, const void *b);
int porownajRokProdukcji(const void *a, const void *b);
int porownajRezyser(const void *a, const void *b);

void czyscKonsole();

int zamknijProgram();

unsigned int generujNoweId(struct Film *bazaDanych, int liczbaRekordow);

int main()
{
    system("color 9");
    struct Film *bazaDanych = NULL;
    int liczbaRekordow = 0;
    int pojemnosc = 0;
    int jestZapisane = 1;

    menu(&bazaDanych, &liczbaRekordow, &pojemnosc, &jestZapisane);

    // Zwolnienie alokowanej pamięci
    free(bazaDanych);

    return 0;
}


void menu(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc, int *jestZapisane)
{
    int wybor;

    do
    {
        printf("##########################################\n");
        printf("#                                        #\n");
        printf("#                 MENU                   #\n");
        printf("#                                        #\n");
        printf("##########################################\n");
        printf("#                                        #\n");
        printf("#      1 - Wczytaj baze                  #\n");
        printf("#      2 - Zapisz baze                   #\n");
        printf("#      3 - Dodaj rekord                  #\n");
        printf("#      4 - Usun rekord                   #\n");
        printf("#      5 - Wypisz baze                   #\n");
        printf("#      6 - Sortuj rekordy                #\n");
        printf("#      7 - Wyczysc konsole               #\n");
        printf("#      8 - Znajdz film                   #\n");
        printf("#      9 - Edytuj rekord                 #\n");
        printf("#      12 - Zamknij program              #\n");
        printf("#                                        #\n");
        printf("##########################################\n");

        scanf("%d", &wybor);

        switch (wybor)
        {
        case 1:
            wczytajBaze(bazaDanych, liczbaRekordow, pojemnosc, jestZapisane);
            break;
        case 2:
            zapiszBaze(bazaDanych, *liczbaRekordow, jestZapisane);
            break;
        case 3:
            dodajRekord(bazaDanych, liczbaRekordow, pojemnosc);
            *jestZapisane = 0;
            break;
        case 4:
            usunRekord(bazaDanych, liczbaRekordow, pojemnosc);
            *jestZapisane = 0;
            break;
        case 5:
            wypiszBaze(*bazaDanych, *liczbaRekordow);
            break;
        case 6:
            sortujRekordy(*bazaDanych, *liczbaRekordow);
            break;
        case 7:
            czyscKonsole();
            break;
        case 8:
            znajdzFilm(*bazaDanych, *liczbaRekordow);
            break;
        case 9:
            edytujRekord(*bazaDanych, *liczbaRekordow);
            break;
        case 12:
            zamknijProgram();
            break;

        default:
            printf("Blad wyboru dzialania! Podaj poprawna wartosc.\n\n");
            break;
        }

    } while (wybor != 12);
}


void wczytajBaze(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc, int *jestZapisane)
{
    // Sprawdź, czy baza danych jest już wczytana
    if (*jestZapisane == 0)
    {
        printf("Baza danych jest juz wczytana. Czy na pewno chcesz nadpisac aktualna baze? (T/N): ");
        char odpowiedz;
        scanf(" %c", &odpowiedz);

        if (odpowiedz != 'T' && odpowiedz != 't')
        {
            printf("Anulowano wczytywanie nowej bazy danych.\n\n");
            return;
        }
        else
        {
            // Zwolnij poprzednią bazę przed wczytaniem nowej
            free(*bazaDanych);
            *liczbaRekordow = 0;
        }
    }

    char nazwaPliku[50];

    printf("Podaj nazwe pliku bazy danych (z rozszerzeniem): ");
    scanf("%s", nazwaPliku);

    FILE *baza = fopen(nazwaPliku, "rb");

    if (baza == NULL)
    {
        perror("Blad otwarcia bazy danych.\n\n");
    }
    else
    {

        //przesuniecie na koniec pliku
        fseek(baza, 0, SEEK_END);

        //filesize to rozmiar pliku - calej bazy danych
        long fileSize = ftell(baza);
        fseek(baza, 0, SEEK_SET);

        //obliczanie liczby rekordow
        *liczbaRekordow = fileSize / sizeof(struct Film);

        // Zarezerwuj pamięć dla bazy danych
        *bazaDanych = malloc(fileSize);

        fread(*bazaDanych, sizeof(struct Film), *liczbaRekordow, baza);

        printf("\nBaza wczytana pomyslnie.\n\n");
        *jestZapisane = 1; // Oznacz bazę jako wczytaną i bez zmian
    }

    fclose(baza);
}

void zapiszBaze(struct Film **bazaDanych, int liczbaRekordow, int *jestZapisane)
{
    char odpowiedz;
    char nazwaPliku[50];

    if (liczbaRekordow == 0)
    {
        printf("Baza danych jest pusta. Czy na pewno chcesz zapisac pusta baze danych? (T/N): ");
        scanf(" %c", &odpowiedz);

        if (odpowiedz != 'T' && odpowiedz != 't')
        {
            printf("Anulowano zapis bazy danych.\n\n");
            return;
        }
    }

    printf("Czy chcesz stworzyc nowy plik (N) czy zaktualizowac istniejacy (Z)? ");
    scanf(" %c", &odpowiedz);

    FILE *baza;
    if (odpowiedz == 'N' || odpowiedz == 'n')
    {
        printf("Podaj nazwe nowego pliku (z rozszerzeniem): ");
        scanf("%s", nazwaPliku);

        baza = fopen(nazwaPliku, "wb");
    }
    else if (odpowiedz == 'Z' || odpowiedz == 'z')
    {
        printf("Podaj nazwe istniejacego pliku (z rozszerzeniem): ");
        scanf("%s", nazwaPliku);

        baza = fopen(nazwaPliku, "wb");
    }
    else
    {
        printf("Niepoprawna odpowiedz. Anulowanie zapisu bazy danych.\n\n");
        return;
    }

    if (baza == NULL)
    {
        perror("Blad otwarcia bazy danych do zapisu.\n\n");
    }
    else
    {
        fwrite(*bazaDanych, sizeof(struct Film), liczbaRekordow, baza);

        fclose(baza);
        printf("Baza danych zapisana.\n\n");

        *jestZapisane = 1; // Zmiana wartości wskaźnika na zapisane
    }
}


void dodajRekord(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc)
{
    struct Film nowyFilm;

    // Zwieksz rozmiar tablicy za pomoca realloc
    struct Film *tmp = realloc(*bazaDanych, (*liczbaRekordow + 1) * sizeof(struct Film));
    if (tmp == NULL)
    {
        printf("\nBlad realokacji pamieci dla bazy danych.\n\n");
        return;
    }
    *bazaDanych = tmp;

    // Przypisz unikalne id
    nowyFilm.id = generujNoweId(*bazaDanych, *liczbaRekordow);

    printf("\nPodaj nazwe filmu: ");
    fflush(stdin); // Wyczyszczenie bufora wejœciowego przed uzyciem fgets

    fgets(nowyFilm.nazwa, sizeof(nowyFilm.nazwa), stdin);
    nowyFilm.nazwa[strcspn(nowyFilm.nazwa, "\n")] = '\0'; // Usuniecie znaku nowej linii

    printf("Podaj rok produkcji: ");
    scanf("%d", &nowyFilm.rokProdukcji);

    printf("Podaj rezysera: ");
    fflush(stdin);

    fgets(nowyFilm.rezyser, sizeof(nowyFilm.rezyser), stdin);
    nowyFilm.rezyser[strcspn(nowyFilm.rezyser, "\n")] = '\0'; // Usuniecie znaku nowej linii

    // Dodaj nowy rekord do bazy
    (*bazaDanych)[*liczbaRekordow] = nowyFilm;
    (*liczbaRekordow)++;

    // Sortuj bazę danych po ID
    qsort(*bazaDanych, *liczbaRekordow, sizeof(struct Film), porownajId);

    printf("\nRekord dodany do bazy.\n\n");
}


void usunRekord(struct Film **bazaDanych, int *liczbaRekordow, int *pojemnosc)
{
    int idDoUsuniecia = -1;

    while (idDoUsuniecia < 0)
    {
        printf("Podaj ID rekordu do usuniecia: ");
        scanf("%u", &idDoUsuniecia);
        fflush(stdin);
    }


    int indeksDoUsuniecia = 0;
    // Znajdź indeks rekordu do usunięcia na podstawie podanego ID
    for (int i = 0; i < *liczbaRekordow; ++i)
    {
        if ((*bazaDanych)[i].id == idDoUsuniecia)
        {
            indeksDoUsuniecia = i;
            break;
        }
    }

    if (indeksDoUsuniecia != 0)
    {
        // Przesuń rekordy, aby usunąć dany rekord
        for (int i = indeksDoUsuniecia; i < *liczbaRekordow - 1; ++i)
        {
            (*bazaDanych)[i] = (*bazaDanych)[i + 1];
        }

        (*liczbaRekordow)--;

        // Zmniejsz rozmiar tablicy za pomocą realloc
        struct Film *tmp = realloc(*bazaDanych, *liczbaRekordow * sizeof(struct Film));
        if (tmp == NULL)
        {
            printf("Blad realokacji pamieci dla bazy danych.\n\n");
            return;
        }
        *bazaDanych = tmp;

        printf("Rekord o ID %u usuniety z bazy.\n\n", idDoUsuniecia);
    }
    else
    {
        printf("Nie znaleziono rekordu o podanym ID.\n");
    }
}


// Funkcja do wyświetlania bazy danych filmów
void wypiszBaze(struct Film *bazaDanych, int liczbaRekordow) {
    if (liczbaRekordow == 0) {
        printf("\nBaza danych jest pusta.\n\n");
        return;
    }

    printf("============================================================================================================\n");
    printf("|   ID   |             Nazwa             | Rok Produkcji |         Rezyser       | Czas | Opis                           | Data Dodania\n");
    printf("============================================================================================================\n");

    for (int i = 0; i < liczbaRekordow; ++i) {
        printf("| %6u | %-30s | %-13d | %-23s | %-4hd | %-30s | %02d-%02d-%04d\n",
               bazaDanych[i].id, bazaDanych[i].nazwa, bazaDanych[i].rokProdukcji,
               bazaDanych[i].rezyser, bazaDanych[i].czas, bazaDanych[i].opis,
               bazaDanych[i].dataDodania.dzien, bazaDanych[i].dataDodania.miesiac, bazaDanych[i].dataDodania.rok);
        printf("============================================================================================================\n");
    }
}

void sortujRekordy(struct Film *bazaDanych, int liczbaRekordow)
{
    int wyborSortowania;

    printf("\nWybierz kryterium sortowania:\n");
    printf("1 - ID\n");
    printf("2 - Nazwa\n");
    printf("3 - Rok Produkcji\n");
    printf("4 - Rezyser\n");

    scanf("%d", &wyborSortowania);

    switch (wyborSortowania)
    {
    case 1:
        qsort(bazaDanych, liczbaRekordow, sizeof(struct Film), porownajId);
        break;
    case 2:
        qsort(bazaDanych, liczbaRekordow, sizeof(struct Film), porownajNazwa);
        break;
    case 3:
        qsort(bazaDanych, liczbaRekordow, sizeof(struct Film), porownajRokProdukcji);
        break;
    case 4:
        qsort(bazaDanych, liczbaRekordow, sizeof(struct Film), porownajRezyser);
        break;
    default:
        printf("Niepoprawny wybor kryterium sortowania.\n");
        return;
    }

    printf("Rekordy posortowane wedlug wybranego kryterium.\n\n");
}

// Funkcja strcmp porównuje dwa słowa.
// Zwraca:
// 1) -1, jeśli pierwsze słowo jest przed drugim w alfabecie.
// 2) 0, jeśli słowa są takie same.
// 3) 1, jeśli drugie słowo jest przed pierwszym w alfabecie.

//Parametry Quicksort
    /* Parametr 1 to wskaźnik na początek tablicy. */
    /* Parametr 2 to liczba elementów w tablicy. */
    /* Parametr 3 to rozmiar pojedynczego elementu w bajtach. */
    /* Parametr 4 to wskaźnik na funkcję porównującą elementy. */

int porownajId(const void *a, const void *b)
{
    return ((const struct Film *)a)->id - ((const struct Film *)b)->id;
}

int porownajNazwa(const void *a, const void *b)
{
    return strcmp(((const struct Film *)a)->nazwa, ((const struct Film *)b)->nazwa);
}

int porownajRokProdukcji(const void *a, const void *b)
{
    return ((const struct Film *)a)->rokProdukcji - ((const struct Film *)b)->rokProdukcji;
}

int porownajRezyser(const void *a, const void *b)
{
    return strcmp(((const struct Film *)a)->rezyser, ((const struct Film *)b)->rezyser);
}



unsigned int generujNoweId(struct Film *bazaDanych, int liczbaRekordow)
{
    // Sprawdź, czy baza danych jest pusta
    if (liczbaRekordow == 0)
    {
        return 1; // Jeśli pusta, zwróć id równa 1
    }

    // Posortuj bazę danych według id
    qsort(bazaDanych, liczbaRekordow, sizeof(struct Film), porownajId);

    // Znajdź pierwsze dostępne id
    unsigned int noweId = 1;

    for (int i = 0; i < liczbaRekordow; ++i)
    {
        if (bazaDanych[i].id == noweId)
        {
            // Jeśli id już istnieje, zwiększ noweId
            noweId++;
        }
        else if (bazaDanych[i].id > noweId)
        {
            // Jeśli znaleziono lukę w sekwencji id, zwróć noweId
            return noweId;
        }
    }

    // Jeśli wszystkie id od 1 do liczbaRekordow są zajęte, zwróć noweId równe liczbaRekordow + 1
    return noweId;
}


void czyscKonsole()
{
    system("cls");
}


void znajdzFilm(struct Film *bazaDanych, int liczbaRekordow)
{
    int wybor;

    while (wybor != 1 && wybor != 2)
    {
        printf("Wybierz kryterium wyszukiwania:\n");
        printf("1 - nazwa\n");
        printf("2 - rok produkcji (zakres lat)\n");
        scanf("%d", &wybor);
    }

    switch (wybor)
    {
    case 1:
        {
            char szukanaFraza[100];
            int znalezioneFilmy = 0;

            printf("\nPodaj szukana nazwe filmu: ");
            scanf("%s", szukanaFraza);

            // Zamień frazę na małe litery dla porównania niezależnie od wielkości liter
            char szukanaFrazaLowerCase[100];
            strcpy(szukanaFrazaLowerCase, szukanaFraza);
            for (int i = 0; szukanaFrazaLowerCase[i]; i++)
            {
                szukanaFrazaLowerCase[i] = tolower(szukanaFrazaLowerCase[i]);
            }

            printf("\nWyniki wyszukiwania:\n");

            for (int i = 0; i < liczbaRekordow; i++)
            {
                // Zamień nazwę filmu na małe litery dla porównania niezależnie od wielkości liter
                char nazwaLowerCase[50];
                strcpy(nazwaLowerCase, bazaDanych[i].nazwa);
                for (int j = 0; nazwaLowerCase[j]; j++)
                {
                    nazwaLowerCase[j] = tolower(nazwaLowerCase[j]);
                }

                // Sprawdź, czy fraza występuje w nazwie filmu lub czy istnieje podobieństwo
                if (strstr(nazwaLowerCase, szukanaFrazaLowerCase) != NULL)
                {
                    wypiszFilm(&bazaDanych[i]);
                    znalezioneFilmy++;
                }
            }

            if (znalezioneFilmy == 0)
            {
                printf("\nNie znaleziono filmu o podanej nazwie lub podobnym tytule.\n");
            }
        }
        break;

    case 2:
        {
            int rokOd, rokDo;

            while (1)
            {
                printf("\nPodaj zakres lat produkcji (od do): ");
                if (scanf("%d %d", &rokOd, &rokDo) != 2 || rokOd > rokDo)
                {
                    printf("Bledny zakres lat. Sprobuj ponownie.\n");
                    while (getchar() != '\n');
                }
                else
                {
                    break;
                }
            }

            int znalezioneFilmy = 0;

            printf("\nWyniki wyszukiwania:\n");

            for (int i = 0; i < liczbaRekordow; i++)
            {
                if (bazaDanych[i].rokProdukcji >= rokOd && bazaDanych[i].rokProdukcji <= rokDo)
                {
                    wypiszFilm(&bazaDanych[i]);
                    znalezioneFilmy++;
                }
            }

            if (znalezioneFilmy == 0)
            {
                printf("\nNie znaleziono filmu w podanym zakresie lat.\n");
            }
        }
        break;
    }
}


void wypiszFilm(const struct Film *film)
{
    printf("\n==========================================\n");
    printf("Id:            %u\n", film->id);
    printf("Nazwa:         %s\n", film->nazwa);
    printf("Rok produkcji: %d\n", film->rokProdukcji);
    printf("Rezyser:       %s\n", film->rezyser);
    printf("==========================================\n");
}

void edytujRekord(struct Film *bazaDanych, int *liczbaRekordow)
{
    unsigned int rekordDoEdycji;
    unsigned int indeksDoEdycji;

    do
    {
        printf("\nPodaj id rekordu do edycji (0 - %d): ", *liczbaRekordow - 1);
        scanf("%u", &rekordDoEdycji);
    }
    while (rekordDoEdycji >= *liczbaRekordow);

    // Pętla szukająca rekordu w bazie danych o podanym id - poszukiwany jest indeks w tablicy
    for (int i = 0; i < *liczbaRekordow; i++)
    {
        if (bazaDanych[i].id == rekordDoEdycji)
        {
            indeksDoEdycji = i;
            break;
        }
    }

    printf("\nPodaj nowe dane do podanego rekordu z bazy danych.");
    printf("\nJesli dane maja pozostac bez zmian, wpisz nd.");
    printf("\nUwaga! Data wprowadzenia do bazy danych nie moze zostac zmieniona!\n");

    char temp_nazwa[50];
    int temp_rokProdukcji;
    char temp_rezyser[50];
    short int temp_czas;
    char temp_opis[200];

    do
    {
        printf("Nowa nazwa (%s): ", bazaDanych[indeksDoEdycji].nazwa);
        fflush(stdin); // Wyczyszczenie bufora wejsciowego przed uzyciem fgets
        fgets(temp_nazwa, sizeof(temp_nazwa), stdin);
        temp_nazwa[strcspn(temp_nazwa, "\n")] = '\0'; // Usuniecie znaku nowej linii
    }
    while (strcmp(temp_nazwa, "nd") != 0 && (strlen(temp_nazwa) <= 3 || strlen(temp_nazwa) >= 49));

    do
    {
        printf("Nowy rok produkcji (%d): ", bazaDanych[indeksDoEdycji].rokProdukcji);
        if (scanf("%d", &temp_rokProdukcji) != 1 || (strcmp(temp_nazwa, "nd") != 0 && (temp_rokProdukcji <= 1000 || temp_rokProdukcji >= 9999)))
        {
            printf("Blad! Wprowadz poprawny rok produkcji.\n");
            while (getchar() != '\n'); // Czyszczenie bufora wejściowego
        }
    }
    while (strcmp(temp_nazwa, "nd") != 0);

    do
    {
        printf("Nowy rezyser (%s): ", bazaDanych[indeksDoEdycji].rezyser);
        fflush(stdin);
        fgets(temp_rezyser, sizeof(temp_rezyser), stdin);
        temp_rezyser[strcspn(temp_rezyser, "\n")] = '\0'; // Usuniecie znaku nowej linii
    }
    while (strcmp(temp_rezyser, "nd") != 0 && (strlen(temp_rezyser) <= 5 || strlen(temp_rezyser) >= 49));

    printf("Nowy czas trwania (%hd): ", bazaDanych[indeksDoEdycji].czasTrwania);
    scanf("%hd", &temp_czas);
    fflush(stdin);

    do
    {
        printf("Nowy opis (%s): ", bazaDanych[indeksDoEdycji].opis);
        fflush(stdin);
        fgets(temp_opis, sizeof(temp_opis), stdin);
        temp_opis[strcspn(temp_opis, "\n")] = '\0'; // Usuniecie znaku nowej linii
    }
    while (strcmp(temp_opis, "nd") != 0 && (strlen(temp_opis) <= 25 || strlen(temp_opis) >= 199));

    printf("Dane zaktualizowane!\n");
}


int zamknijProgram()
{
    printf("Do widzenia!");
    return 0;
}
