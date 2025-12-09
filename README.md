# 🤖 MINIPEKKA V1 – Robot con braccio meccanico

## 📌 Descrizione
**MINIPEKKA V1** è un robot programmato su piattaforma **Arduino** dotato di:
- Braccio meccanico con **motori dedicati** .
- Sensore a ultrasuoni per rilevare ostacoli.
- Sensore di linea per seguire percorsi predefiniti se presenti.
- Memoria EEPROM per "ricordare" se sta trasportando un oggetto.

Il suo scopo principale è:
1. **Rilevare un oggetto** con il sensore a ultrasuoni.
2. **Afferrare l’oggetto** con il braccio meccanico.
3. **Trasportarlo lungo un percorso** seguendo la linea (qualora il percorso sia presente).
4. **Rilasciarlo nel punto di scarico** quando il robot si ferma.
5. **Resettare il braccio** per prepararsi a una nuova operazione.

---

## ⚙️ Componenti utilizzati
- **Motori DC**:
  - `motor_9`: motore destro (movimento).
  - `motor_10`: motore sinistro (movimento).
  - `motor_1`: motore di presa (stringe/allarga).
  - `motor_2`: motore di sollevamento (alza/abbassa).
- **Sensori**:
  - `ultrasonic_8`: sensore a ultrasuoni per rilevare oggetti entro 16 cm.
  - `linefollower_6`: sensore di linea per seguire il percorso.
- **EEPROM**: memoria per salvare lo stato del braccio (oggetto preso o meno).

---

## 🚀 Funzionamento
1. **Avvio**:
   - Se non ha un oggetto (`robapresa == 0`), il braccio viene resettato (aperto e alzato).
   - Il robot parte in avanti.

2. **Rilevamento ostacolo**:
   - Se un oggetto viene rilevato a meno di 16 cm e il robot non trasporta nulla:
     - Si ferma.
     - Chiude il braccio (`motor_1.run(100)`).
     - Abbassa il braccio (`motor_2.run(-100)`).
     - Aggiorna lo stato in EEPROM (`robapresa = 1`).

3. **Scarico**:
   - Quando raggiunge il punto di stop (linea bianca), se ha un oggetto:
     - Lo rilascia.
     - Resetta il braccio.
     - Aggiorna lo stato (`robapresa = 0`).

---

## 🔄 Funzioni principali del codice
- `resetbraccio()`: apre e alza il braccio.
- `_delay(s)`: funzione di attesa.
- `setup()`: logica principale del robot (loop infinito).

---

## 📖 Flusso operativo
1. **Start → Reset braccio → Avanzamento**
2. **Rilevamento oggetto → Presa → Trasporto**
3. **Arrivo al punto di scarico → Rilascio → Reset braccio**
4. **Ripetizione ciclo**

---

## 🎯 Obiettivo
Il robot **MINIPEKKA V1** è progettato per automatizzare la raccolta e il rilascio di piccoli oggetti.