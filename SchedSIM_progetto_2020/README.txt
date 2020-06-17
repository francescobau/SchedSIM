Come usare il programma:
- Il programma va subito alla ricerca di un file chiamato come dalla macro FILE_NAME in Utils_main.h .
  Assicurarsi che tale file di testo sia presente, e che i dati dei processi siano inseriti correttamente.

- Se si avvia il programma passando un argomento diverso da 0, viene avviata la modalita' di debug.	

- Se i dati dei processi vengono importati correttamente, allora si apre il menu principale.
  Da li' l'utente puo' scegliere quale algoritmo di scheduling applicare:
  1) FCFS (First Come, First Served)
  2) RR (Round Robin)
  3) PS (Priority Scheduling)
  4) SPN (Shortest Process Next) [attualmente non disponibile]
  5) SRT (Shortest Remaining Time) [attualmente non disponibile]
  
  Se si vuole chiudere il programma, basta inserire 0.