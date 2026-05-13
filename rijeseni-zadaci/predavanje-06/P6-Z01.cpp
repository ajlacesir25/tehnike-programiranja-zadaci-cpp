// Funkcija GenerirajStepeneDvojke, jedan parametar n -> dinamički alocira niz
// od n brojeva. Tip brojeva se zadaje kasnije, npr.
// GenerirajStepeneDvojke<double>. Za n <= 0 funkcija baca izuzetak domain_error
// s porukom "Broj elemenata mora biti pozitivan". Ako alokacija ne uspije,
// funkcija baca izuzetak runtime_error s porukom "Alokacija nije uspjela".
// Nakon alokacije, funkcija puni alocirani niz s prvih n stepena broja 2.
// Ukoliko dođe do prekoračenja opsega tipa, baca izuzetak tipa overflow_error
// s porukom "Prekoračen dozvoljeni opseg".
// Kao rezultat funkcija vraća pokazivač na prvi element tako alociranog niza.
// Testni program: Sa tastature se unosi broj n, poziva se funkcija,
// a niz se ispisuje na ekran.
// U testnom programu treba predvidjeti hvatanje svih izuzetaka.

#include <iostream>
#include <limits>
#include <stdexcept>

template <typename Tip> Tip *GenerirajStepeneDvojke(int n) {
  if (n <= 0)
    throw std::domain_error("Broj elemenata mora biti pozitivan");
  Tip *pok_niz{};

  try {
    pok_niz = new Tip[n];
  } catch (...) {
    throw std::runtime_error("Alokacija nije uspjela");
  }

  Tip stepen = 1;
  for (int i = 0; i < n; i++) {
    pok_niz[i] = stepen;
    if (i != n - 1)
      if (stepen <= std::numeric_limits<Tip>::max() / 2)
        stepen *= 2;
      else
        throw std::overflow_error("Prekoracen dozvoljeni opseg");
  }
  return pok_niz;
}

int main() {
  int n;
  std::cout << "Koliko zelite elemenata: ";
  std::cin >> n;
  try {
    auto niz = GenerirajStepeneDvojke<unsigned long long int>(n);
    for (int i = 0; i < n; i++)
      std::cout << niz[i] << " ";
    delete[] niz;
  } catch (std::exception &e) {
    std::cout << "Izuzetak: " << e.what();
  }
  return 0;
}
