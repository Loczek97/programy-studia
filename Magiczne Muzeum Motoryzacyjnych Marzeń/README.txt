Magiczne Muzeum Motoryzacyjnych Marzeń to strona internetowa fikcyjnego muzeum sportowych motoryzacyjnych klasyków z lat 1945 - 2000. Storna internetowa składa się z trzech podstron: strony głównej, "wirtualnego muzeum" oraz strony informacyjnej. Był to projekt grupowy, w którym odpowiadałem za stronę wirtualnego muzeum oraz dostosowanie arkuszy stylów strony pod RWD (Responsive Web Design).

Wirtualne muzeum to strona z galerią pojazdów dostępnych dla oglądających w naszym muzeum. Dane o pojazdach oraz ich opisy są pobierane symulacji bazy danych w postaci pliku .json za pomocą JavaScriptu. ze względu na zalecenia prowadzącego, strona nie mogła korzystać z żadnych bibliotek oraz systemów bazodanowych, dlatego wybór padł na zastosowanie takiego rozwiązania. 

Podstrona zawiera panel z filtrami, dzięki którym można wybrać typ samochodu (sportowy, supersamochód i muscle) oraz przedział lat, w którym dany samochód został wyprodukowany.

Strona jest opublikowana na hostingu deweloperskim, link do repozytorium oraz podglądu w drugim pliku.

UWAGA! Strona do poprawnego działania potrzebuje serwera (lokalnego lub hostingu) do poprawnego działania ze względu na zastosowanie funkcji fetch(). Uruchomienie pobranej wersji pliku index.html poskutkuje niepoprawnym funkcjonowaniem podstrony wirtualnego muzeum.