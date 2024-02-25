#include <stddef.h>
#include "cnf.h"

//
// LOGIN: <xuhliar00>
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // ZDE PRIDAT KOD
    for(int ulica = 0; ulica < num_of_streets; ulica++) {
        Clause* klauzura = create_new_clause(formula);
        for(int dalsia_ulica = 0; dalsia_ulica < num_of_streets; dalsia_ulica++) {
            add_literal_to_clause(klauzura, true, ulica, streets[dalsia_ulica].crossroad_from, streets[dalsia_ulica].crossroad_to);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    for (int i = 0; i < num_of_streets; i++) {
        for(int j = 0; j < num_of_crossroads; j++) {
            for (int k = 0; k < num_of_crossroads; k++) {
                for(int l = 0; l < num_of_crossroads; l++){
                    for(int m = 0; m < num_of_crossroads; m++){
                        if(j == l && k == m){
                            continue;
                        }
                        Clause* klauzura = create_new_clause(formula);
                        add_literal_to_clause(klauzura, false, i, j, k);
                        add_literal_to_clause(klauzura, false, i, l, m);
                    }
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    for(int ulica = 0; ulica < num_of_streets; ulica++){
        for(int zaciatok_krizovatky = 0; zaciatok_krizovatky < num_of_crossroads; zaciatok_krizovatky++){
            for(int koniec_krizovatky = 0; koniec_krizovatky < num_of_crossroads; koniec_krizovatky++){
                Clause* klauzura = create_new_clause(formula);
                add_literal_to_clause(klauzura, false, ulica, zaciatok_krizovatky, koniec_krizovatky);
                for(int krizovatka_2 = 0; krizovatka_2 < num_of_crossroads; krizovatka_2++){
                    add_literal_to_clause(klauzura, true, ulica+1, koniec_krizovatky, krizovatka_2);
                }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
    for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
