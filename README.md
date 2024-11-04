# Tema2_Robotica

## Descrierea Task-ului
În această temă am creat un joc asemanator cu TypeRacer.

Jocul este în repaus. LED-ul RGB are culoarea albă.
Se alege dificultatea jocului folosind butonul de dificultate, iar în terminal va apărea “Easy/Medium/Hard mode on!”.
Se apasă butonul de start/stop.
LED-ul clipește timp de 3 secunde, iar în terminal se va afișa numărătoarea înversă: 3, 2, 1.
LED-ul devine verde și încep să apară cuvinte de tastat.
La tastarea corectă, următorul cuvânt apare imediat. Dacă nu se tasteaza cuvântul în timpul stabilit de dificultate, va apărea un nou cuvânt.
O greșeală face LED-ul să devină roșu. Pentru a corecta cuvântul, se va folosi tasta BackSpace.
Dupa 30 de secunde, runda se termină, iar în terminal se va afișa scorul: numărul total de cuvinte scrise corect.
Jocul se poate opri oricând cu butonul de start/stop.

## Cerinte
LED RGB - Indicator de stare:

În starea de repaus, LED-ul va avea culoarea albă.
La apăsarea butonului de start, LED-ul va clipi timp de 3 secunde, indicând o numărătoare inversă până la începerea rundei.
În timpul unei runde: LED-ul va fi verde dacă textul introdus este corect și va deveni roșu în caz de greșeală.
(1p) Butonul Start/Stop:

Modul de repaus: Dacă jocul este oprit, apăsarea butonului inițiază o nouă rundă după o numărătoare inversă de 3 secunde.
În timpul unei runde: Dacă runda este activă, apăsarea butonului o va opri imediat.
(1p) Butonul de dificultate:

Butonul de dificultate controlează viteza cu care apar cuvintele și poate fi folosit doar în starea de repaus.
La fiecare apăsare, dificultatea se schimbă ciclind între: (Easy, Medium, Hard).
La schimbarea dificultății, se trimite un mesaj prin serial: “Easy/Medium/Hard mode on!”.
Generarea cuvintelor:

Se va crea un dicționar de cuvinte.
În timpul unei runde, cuvintele vor fi afișate în terminal într-o ordine aleatorie.
Dacă cuvântul curent a fost scris corect, un cuvânt nou va fi afișat imediat. Dacă nu, un nou cuvânt va apărea după intervalul de timp stabilit în funcție de dificultate.

## Componente
Arduino UNO (ATmega328P microcontroller)
1x LED RGB (pentru a semnaliza dacă cuvântul corect e scris greșit sau nu)
2x Butoane (pentru start/stop rundă și pentru selectarea dificultății)
5x Rezistoare (3x 220/330 ohm, 2x 1000 ohm)
Breadbord
Fire de legătură

## Schema electrica
![Tema2_Robotica](https://github.com/user-attachments/assets/7ab3cd3f-c72e-4ab8-b482-f0c432b2cb88)

## Poze si link cu functionalitatea montajului fizic

![WhatsApp Image 2024-11-05 at 01 16 20_f1b6828a](https://github.com/user-attachments/assets/a9558d17-049d-45bf-a77e-a97fd000a88b)
![WhatsApp Image 2024-11-05 at 01 16 20_9519fd7a](https://github.com/user-attachments/assets/363ea63a-2d37-4a63-84fe-401a9bde1bb5)
![WhatsApp Image 2024-11-05 at 01 16 20_378e7ecc](https://github.com/user-attachments/assets/d3e90875-4b2c-4077-a84a-598f727c18df)


https://github.com/user-attachments/assets/d3de678c-a7c7-4da6-8d06-2c09f31b70b2

