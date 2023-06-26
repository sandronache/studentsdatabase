#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main() {
    printf("Salut!\nNe bucuram ca ai ales acest program pentru a te ajuta cu manageriatul bazei tale de date!\n\n");
    printf("Cum doresti sa procedam?\n1. Plecam de la o baza de date deja conceputa.\n2. Incepem o baza de date noua\n\nAlegeti 1 sau 2:\n");
    
    int response;
    scanf("%d", &response);

    while(response != 1 && response != 2) {
        printf("Alegere invalida, reincercati:\n");
        scanf("%d", &response);
    }
   
    Tree tree = NULL;
    char last_name[100];
    char first_name[100];
    int id;
    char group[10];
    float average_grade;

    if(response == 1) {
        FILE* fin;
        while(1) {
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("Va rugam introduceti numele documentului!\n\n!!!   Pentru ca acest program sa functioneze avem urmatoarele reguli:   !!!!\n");
            printf("Documentul sa fie unul anterior conceput de programul nostru sau sa indeplineasca anumite reguli:\n");
            printf("->sa fie de tip .txt;\n");
            printf("->sa se afle in directorul curent;\n");
            printf("->sa aiba studentii in orice ordine, dar cu datele scrise in formatul urmator:\n(nume pe o linie, prenume pe o linie, id-ul pe o linie, ");
            printf("grupa pe o linie si media pe o linie), fara alte spatii sau linii aditionale.\n");
            printf("->sa nu existe deja un document cu numele 'new_database.txt'\n\n");

            char file_name[50];
            scanf("%s", file_name);
            fin = fopen(file_name, "r");
            if (fin == NULL) {
                printf("---------------------------------------------------------------------------------------\n");
                printf("Nu am reusit sa deschidem fisierul! Doriti sa reincercati?\n\n1.Da\n2.Nu\n\nAlegeti 1 sau 2:\n");
                scanf("%d", &response);
                while(response != 1 && response != 2) {
                    printf("Alegere invalida, reincercati:\n");
                    scanf("%d", &response);
                }
                if(response == 1)
                    continue;
                else {
                    printf("-------------------------------------\n");
                    printf("La revedere!\n");
                    return 0;
                }
            } else {
                break;
            }
        }
        while(fscanf(fin, "%s", last_name) == 1) {
            fscanf(fin, "%s", first_name);
            fscanf(fin, "%d", &id);
            fscanf(fin, "%s", group);
            fscanf(fin, "%f", &average_grade);
            tree = insert(tree, last_name, first_name, id, group, average_grade);
        }
        fclose(fin);
    }
    FILE* fout = fopen("new_database.txt", "w");
    while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Ce operatiune doriti sa executati?\n\n");
        printf("1. Adauga student.\n");
        printf("2. Sterge un student.\n");
        printf("3. Modifica datele unui student.\n");
        printf("4. Cauta un student.\n");
        printf("5. Calculeaza media generala a institutiei.\n");
        printf("6. Afiseaza statistici.\n");
        printf("7. Exit\n\n");
        printf("Tastati numarul corespunzator operatiei de interes:\n");
        scanf("%d", &response);
        while(response < 1 || response > 7) {
            printf("Alegere invalida, reincercati:\n");
            scanf("%d", &response);
        }
        if(response == 1) {
            while(1) {
                printf("------------------------------------------------------------------------\n");
                printf("Va rugam frumos sa introduceti datele despre student:\n\n");
                printf("Nume: ");
                scanf("%s", last_name);
                printf("\n");
                printf("Prenume: ");
                scanf("%s", first_name);
                printf("\n");
                printf("Id: ");
                scanf("%d", &id);
                printf("\n");
                printf("Grupa: ");
                scanf("%s", group);
                printf("\n");
                printf("Medie: ");
                scanf("%f", &average_grade);
                printf("\n");
                if(verifyId(tree, id) != 0) {
                    printf("Exista deja un student cu acest Id si nu pot adauga altul!\n\n");
                } else {
                    tree = insert(tree, last_name, first_name, id, group, average_grade);
                }
                printf("------------------------------------------------------------------------\n");
                printf("Doriti sa mai adaugati un student sau sa reveniti la meniu pentru o alta operatiune/iesire program?\n\n");
                printf("1.Adauga alt student.\n2.Inapoi la meniu.\n\nAlegeti 1 sau 2:\n");
                scanf("%d", &response);
                while(response != 1 && response != 2) {
                    printf("Alegere invalida, reincercati:\n");
                    scanf("%d", &response);
                }
                if(response == 1) 
                    continue;
                else
                    break;
            }
        }
        else if(response == 2) {
            while(1) {
                printf("------------------------------------------------------------------------\n");
                printf("Introduceti id-ul:\n");
                scanf("%d", &id);
                if(verifyId(tree, id) == 0) {
                    printf("Nu exista un student cu acest Id!\n\n");
                } else {
                    tree = delete(tree, id);
                    printf("\nStergerea elevului cu id-ul %d reusita!\n\n", id);
                }
                printf("Doriti sa stergeti un alt student sau sa reveniti la meniu pentru o alta operatiune/iesire program?\n\n");
                printf("1.Sterge alt student.\n2.Inapoi la meniu.\n\nAlegeti 1 sau 2:\n");
                scanf("%d", &response);
                while(response != 1 && response != 2) {
                    printf("Alegere invalida, reincercati:\n");
                    scanf("%d", &response);
                }
                if(response == 1) 
                    continue;
                else
                    break;
            }
        }
        else if(response == 3) {
            while(1) {
                printf("------------------------------------------------------------------------\n");
                printf("Introduceti id-ul:\n");
                scanf("%d", &id);
                if(verifyId(tree, id) == 0) {
                    printf("\nNu exista un student cu acest Id!\n\n");
                } else {
                    printf("------------------------------------------------------------------------\n");
                    printf("Ce date doriti sa modificati?\n\n1.Nume.\n2.Prenume.\n3.Grupa.\n4.Media\n\nAlegeti un numar de la 1 la 4:\n");
                    while(response < 1 || response > 4) {
                        printf("Alegere invalida, reincercati:\n");
                        scanf("%d", &response);
                    }
                    scanf("%d", &response);
                    if(response == 1) {
                        printf("------------------------------------------------------------------------\n");
                        printf("Introduceti noul nume:\n");
                        scanf("%s", last_name);
                        replaceLastName(tree, id, last_name);
                    } else if(response == 2) {
                        printf("------------------------------------------------------------------------\n");
                        printf("Introduceti noul prenume:\n");
                        scanf("%s", first_name);
                        replaceFirstName(tree, id, first_name);
                    } else if(response == 3) {
                        printf("------------------------------------------------------------------------\n");
                        printf("Introduceti noua grupa:\n");
                        scanf("%s", group);
                        replaceGroup(tree, id, group);
                    } else if(response == 4) {
                        printf("------------------------------------------------------------------------\n");
                        printf("Introduceti noua medie:\n");
                        float new_average_grade;
                        scanf("%f", &new_average_grade);
                        replaceAverageGrade(tree, id, new_average_grade);
                    }
                }
                printf("------------------------------------------------------------------------\n");
                printf("Doriti sa modificati datele unui alt student sau sa reveniti la meniu pentru o alta operatiune/iesire program?\n\n");
                printf("1.Modifica datele unui alt student.\n2.Inapoi la meniu.\n\nAlegeti 1 sau 2:\n");
                scanf("%d", &response);
                while(response != 1 && response != 2) {
                    printf("Alegere invalida, reincercati:\n");
                    scanf("%d", &response);
                }
                if(response == 1) 
                    continue;
                else
                    break;
            }
        }
        else if (response == 4) {
            while(1) {
                printf("------------------------------------------------------------------------\n");
                printf("Dupa ce caracteristica doriti sa il cautati?\n\n1.Nume.\n2.Prenume.\n3.Nume si Prenume.\n4.Id.\n5.Grupa.\n\nAlegeti un numar de la 1 la 5:\n");
                scanf("%d", &response);
                while(response < 1 || response > 5) {
                        printf("Alegere invalida, reincercati:\n");
                        scanf("%d", &response);
                    }
                if(response == 1) {
                    printf("------------------------------------------------------------------------\n");
                    printf("Introduceti numele:\n");
                    scanf("%s", last_name);
                    printf("\n");
                    if(verifyLastName(tree, last_name) == 0) {
                        printf("Nu exista un student cu acest nume!\n\n");
                    } else {
                        printFromLastName(tree, last_name);
                    }
                } else if(response == 2) {
                    printf("------------------------------------------------------------------------\n");
                    printf("Introduceti prenumele:\n");
                    scanf("%s", first_name);
                    printf("\n");
                    if(verifyFirstName(tree, first_name) == 0) {
                        printf("Nu exista un student cu acest prenume!\n\n");
                    } else {
                        printFromFirstName(tree, first_name);
                    }
                } else if(response == 3) {
                    printf("------------------------------------------------------------------------\n");
                    printf("Introduceti numele: ");
                    scanf("%s", last_name);
                    printf("\n");
                    printf("Introduceti prenumele: ");
                    scanf("%s", first_name);
                    printf("\n");
                    if(verifyFirstName(tree, first_name) == 0 || verifyLastName(tree, last_name) == 0) {
                        printf("Nu exista un student cu acest nume si prenume!\n\n");
                    } else {
                        printFromFirstandLastName(tree, last_name, first_name);
                    }
                } else if(response == 4) {
                    printf("------------------------------------------------------------------------\n");
                    printf("Introduceti id-ul:\n");
                    scanf("%d", &id);
                    printf("\n");
                    if(verifyId(tree, id) == 0) {
                        printf("Nu exista un student cu acest Id!\n\n");
                    } else {
                        printFromId(tree, id);
                    }
                } else if(response == 5) {
                    printf("------------------------------------------------------------------------\n");
                    printf("Introduceti grupa:\n");
                    scanf("%s", group);
                    printf("\n");
                    if(verifyGroup(tree, group) == 0) {
                        printf("Nu exista un student din aceasta grupa!\n\n");
                    } else {
                        printFromGroup(tree, group);
                    }
                }
                printf("------------------------------------------------------------------------\n");
                printf("Doriti sa cautati un alt student sau sa reveniti la meniu pentru o alta operatiune/iesire program?\n\n");
                printf("1.Cautati un alt student.\n2.Inapoi la meniu.\n\nAlegeti 1 sau 2:\n");
                scanf("%d", &response);
                while(response != 1 && response != 2) {
                    printf("Alegere invalida, reincercati:\n");
                    scanf("%d", &response);
                }
                if(response == 1) 
                    continue;
                else
                    break;
            }
        } else if(response == 5) {
            printf("--------------------------------------------------------------------\n");
            float institution_average = calculateSumOfStudentsAverages(tree) / calculateNumberOfStudents(tree);
            printf("Media institutiei este: %0.2f\n", institution_average);
        } else if(response == 6) {
            printf("--------------------------------------------------------------------\n");
            int number_of_students = calculateNumberOfStudents(tree);
            int number_of_students_promoted = calculateNumberOfStudentsPromoted(tree);
            int number_of_students_unpromoted = number_of_students - number_of_students_promoted;
            printf("Procentajul de promovati este: %0.2f\n", (float)number_of_students_promoted / (float)number_of_students * 100);
            printf("Procentajul de nepromovati este: %0.2f\n\n", (float)number_of_students_unpromoted / (float)number_of_students * 100);
            for(int i = 0; i < 10; i++) {
                printf("Procentajul elevilor cu nota trunchiata %d este: %0.2f\n", i, (float)calculateNumberOfStudentsWithGradeI(tree, i)/(float)number_of_students * 100);
            }
            printf("Procentajul elevilor cu nota 10 este: %0.2f\n", (float)calculateNumberOfStudentsWithGradeI(tree, 10)/(float)number_of_students * 100);
        } else {
            printAscending(tree, fout);
            printf("Noua baza de date o gasiti in new_database.txt! La revedere!\n");
            break;
        }
    }
    // freeing used memory
    freeTree(tree);
    // closing file
    fclose(fout);
    return 0;
}