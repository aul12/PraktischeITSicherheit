Vorlage für Seminar-Ausarbeitungen
==================================

Bei der Verwendung für Seminare sollten keine Befehle verwendet werden, die das Layout verändern.
Insbesondere sollte die Zeile `\documentclass[10pt,a4paper,sigconf,language=XXX]{acmart}` intakt bleiben.

Folgende Befehle **sollen** angepasst werden:

* `\title{Titel}` -- Titel der Ausarbeitung.
* `\author{...}` -- Name der Autorin/des Autors.
* `\email{...}` -- E-Mail-Adresse der Autorin/des Autors.
* `acmConference[Seminar Acr.]{Seminar title}{WS/SS XXXX}{Institute of Distributed Systems, Ulm University}` 
- Seminar Akronym = KTT, PRIV, PASF, ATVS oder RTDS
- Titel des Seminars (z.B. *Proseminar Privacy im Internet*) 
- Semester (z.B. *WS 2012/13*).

Die Vorlage kann mit `pdflatex bibtex pdflatex pdflatex` kompiliert werden
