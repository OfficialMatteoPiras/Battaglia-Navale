//Created by Claudia De Carlo

#include "../headers/player.h"
#include "../headers/ship.h"
#include "../headers/coords.h"
#include "../headers/backing.h"


//MAIN con argomenti (A = pcpc | B = pcumano)

    //creare giocatori p1 e p2
    /*player p1, p2;      //p1 sempre computer
    coords origin ("A1");   //inizializzate sulla prima cella
    coords target ("A1");   //inizializzate sulla prima cella
    std::string move;*/

    //vettore log per salvare tutte le mosse (boolean, coords, coords) | (player, origin, target)

    //posizionare navi p1 random
    //posizionare navi p2 (A random | B cout/cin)

    //random primo giocatore: p1 roundFlag = true, p2 roundFlag = false        //(p1 = true, p2 = false)

    //for (int j = 0; j < maxRounds && p1.alive && p2.alive; j++)
        //try (forse meglio due separati dopo)
            //if(roundFlag)     //round P1
                //nave random da p1.fleet e salva in origin
                //(AA AA ?)
                //while (!trova coords target valide per l'azione)
                    //coordinate random
                    //try catch azione

            //else              //round P2
                //while (!done)
                    //try
                        //legge la mossa come stringa

                        //if AA AA  cancella le Y da attack e salva su log
                            //chiede e legge nuova mossa e salva in move

                        //if XX XX  stampa le griglie DI P2
                            //chiede e legge nuova mossa e salva in move

                        //divide in due coords origin e target
                        //controlla se origin è in myShips
                            //se sì chiama l'azione (altrimenti propaga eccezione)
                            //salva roundFlag, origin, target su log
                            //done

                    //catch
                    //chiede di riprovare (done = false)

            // !roundFlag;
        // catch eccezioni varie, messaggi a schermo, decrementa j se no conta un turno non fatto
    //FINE PARTITA
        //if p1 è morto
        //if p2 è morto
        //if mosse finite: confronto "punteggi" (unità vive)