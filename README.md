# Projet-EL-3032 EL FTOUH Khalid/RAHME Jovan

Comment utiliser notre programe :

1-Ouvrir plusieurs terminaux : 
        -Un terminal pour l'application Cliente
        -Un terminal pour le Serveur de Routage
        -2 Terminaux pour les 2 Serveur de Données

2-Faites un cd Pipe dans chaque terminal
3-Placez vous sur un des terminaux (n'importe lequel) et faites un make all (dans le cas ou vous souhaitez supprimer des fichiers .o, faites un make clean)

4-Suivre les prochaines indications pour chaque terminale dans l'ordre où ils sont énoncé



En premier ou en deuxieme le terminal Serveur de Routage :

    Démarer l'exectuable ServRout : ./ServRout



En premier ou en deuxieme les terminaux Serveur de données :

    Démarer l'executable ServD en precisant le serveur de données que vous souhaitez initialisé . Nous possédons 2 serveur de données : 1111 et 2222 . 
    Il faut donc éxectuer les 2 commandes suivantes sur 2 terminaux différents: ./ServD 1111  et ./ServD 2222 
    Dans le cas où le code du serveur n'est aucun des 2 cité plus haut, une erreur s'affichera sur le terminal et vous devrait re lancer les serveurs avec le bon code cette fois.
    


En dernier, le terminal application Cliente :

    Démarer l'executable de la maniere suivante : ./Client CodeServ CodeLieu CodeMenu NumClient(1 ou 2)   les 3 codes devront etre composé de 4 chiffres
    Exemple : ./Client 1111 7742 1234 1


Remarques:
    -Si vous rentrer un mauvais numero Client, il faut stopper le terminal avec un Ctrl C et recommencer en corrigeant
    -Faire la meme chose pour une erreur de Code Serv, Menu ou Lieu mais cette fois il faudra également terminer les autres terminaux de la meme maniere
