/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
  for(int i = 0; i < HT_SIZE; i++){
    (*table)[i] = NULL;
  }
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
  ht_item_t *tmp = (*table)[get_hash(key)];
  while(tmp != NULL){
    if(strcmp(key, tmp->key) == 0){
      return tmp;
    }
    tmp = tmp->next;
  }
  return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
  ht_item_t *tmp = ht_search(table, key);
  if(tmp != NULL){
    tmp->value = value;
    return;
  }
  ht_item_t *key1 = malloc(sizeof(ht_item_t));

  if(key1 == NULL){
    return;
  }

int x = get_hash(key);
key1->key = malloc(sizeof(char)*(strlen(key) + 1));
if(key1->key == NULL){
  free(key1);
  return;
}
strcpy(key1->key, key);
key1->next = (*table)[x];
key1->value = value;
(*table)[x] = key1;
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
  ht_item_t *tmp = ht_search(table, key);
  if(tmp != NULL){
    return &tmp->value;
  }
  return NULL;
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
 if(key != NULL) {
  int x = get_hash(key);
  ht_item_t *tmp = (*table)[x], *delete, *previous;
  while(tmp != NULL){
    if(strcmp(key, tmp->key) == 0){
      if(tmp == (*table)[x]){
        delete = tmp;
        (*table)[x] = tmp->next;
        free(delete->key);
        free(delete);
        return;
      }else{
        previous->next = tmp->next;
        free(tmp->key);
        free(tmp);
        return;
      }
    }
    previous = tmp;
    tmp = tmp->next;
  }
}

}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
  ht_item_t *delete;
  for(int i = 0; i < HT_SIZE; i++){
    while((*table)[i]){
        delete = (*table)[i];
        (*table)[i] = (*table)[i]->next;
        free(delete->key);
        free(delete);
    }
  }
}
