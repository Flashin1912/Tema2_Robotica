#include <Arduino.h>

const int LED_R_PIN = 11;
const int LED_G_PIN = 10;
const int LED_B_PIN = 9;

const int BUTTON_START_PIN = 2;
const int BUTTON_DIFFICULTY_PIN = 3;

const char* words[] = { "apple", "banana", "cherry", "dog", "elephant",
                        "forest", "giraffe", "honey", "island", "jungle",
                        "kitten", "lemon", "mountain", "night", "orange",
                        "piano", "queen", "river", "sun", "tree" };
const int wordCount = 20;

enum GameState { IDLE, COUNTDOWN, ACTIVE, STOPPED };
GameState gameState = IDLE;

enum Difficulty { EASY, MEDIUM, HARD };
Difficulty difficulty = EASY;

unsigned long difficultyTime[] = { 5000, 3500, 2000 };

unsigned long gameStartTime;
unsigned long activeStartTime;
unsigned long currentWordStartTime;  // Timpul de joc

const unsigned long activeDuration = 30000; // Durata jocului

unsigned long lastCountdownUpdate = 0;  

unsigned long lastBlinkTime = 0; 
const unsigned long blinkInterval = 500; 

int correctWordsCount = 0;

String currentWord;
int currentIndex = 0;  // Litera curenta din cuvant

String userInput;

void setRGBColor(int red, int green, int blue) {
    analogWrite(LED_R_PIN, red);
    analogWrite(LED_G_PIN, green);
    analogWrite(LED_B_PIN, blue);
}

void setIdleColor() {
    setRGBColor(255, 255, 255);  // Alb
}

void setCountdownColor() {
    setRGBColor(0, 255, 0);  // Verde
}

void setActiveColor() {
    setRGBColor(0, 255, 0);  // Verde
}

void setErrorColor() {
    setRGBColor(255, 0, 0);  // Rosu
}

void setupButtons() {
    pinMode(BUTTON_START_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DIFFICULTY_PIN, INPUT_PULLUP);
}

void handleStartButton() {
    if (digitalRead(BUTTON_START_PIN) == LOW) {
        if (gameState == IDLE) {
            gameState = COUNTDOWN;
            Serial.println("Starting countdown...");
            gameStartTime = millis();
        } else if (gameState == ACTIVE) {
            gameState = STOPPED;
            Serial.println("Game stopped.");
            Serial.print("Correct words: ");
            Serial.println(correctWordsCount);
            setIdleColor();
        }
    }
    if (gameState == STOPPED) {
        delay(1000);  // Anti-rebound
        gameState = IDLE;
        correctWordsCount = 0;
        setIdleColor();
    }
}

void handleDifficultyButton() {
    if (digitalRead(BUTTON_DIFFICULTY_PIN) == LOW && gameState == IDLE) {
        difficulty = (Difficulty)((difficulty + 1) % 3);
        switch (difficulty) {
            case EASY:
                Serial.println("Easy mode on!");
                break;
            case MEDIUM:
                Serial.println("Medium mode on!");
                break;
            case HARD:
                Serial.println("Hard mode on!");
                break;
        }
        delay(300);  // Anti-rebound
    }
}

void displayRandomWord() {
    int randomIndex = random(0, wordCount);
    currentWord = words[randomIndex];
    currentIndex = 0;
    currentWordStartTime = millis();
    Serial.print("Type this word: ");
    Serial.println(currentWord);
}

void updateGame() {
    if (gameState == COUNTDOWN) {
        unsigned long countdownTime = millis() - gameStartTime;
        if (countdownTime < 3000) {
            if (millis() - lastBlinkTime >= blinkInterval) {
                lastBlinkTime = millis();
                static bool ledOn = false;
                if (ledOn) {
                    setRGBColor(0, 0, 0);  
                } else {
                    setCountdownColor();  
                }
                ledOn = !ledOn;
                
            }
            if (countdownTime - lastCountdownUpdate >= 1000) {
                int secondsLeft = 3 - countdownTime / 1000;
                Serial.print("Starting in: ");
                Serial.println(secondsLeft);
                lastCountdownUpdate = countdownTime;
            }
            
        } else {
            gameState = ACTIVE;
            activeStartTime = millis();
            setActiveColor();
            Serial.println("Game started!");
            displayRandomWord(); 
        }
    }

    if (gameState == ACTIVE) {

        if (millis() - activeStartTime >= activeDuration) {
            gameState = STOPPED;
            Serial.println("Time's up! Game over.");
            Serial.print("Correct words: ");
            Serial.println(correctWordsCount);
            setIdleColor();
            return;
        }

        if (millis() - currentWordStartTime >= difficultyTime[difficulty]) {
            Serial.println("\nTime's up for this word! Moving to next.");
            displayRandomWord(); 
            return;
        }

        if (Serial.available() > 0) {
            char incomingChar = Serial.read();

            // Backspace
            if (incomingChar == '-') {
                if (currentIndex > 0) {
                    currentIndex--;  
                    Serial.print("\b \b");  // Sterge ultimul caracter de pe Serial Monitor
                }
            } 
            // Verificam daca litera introdusa coincide cu litera curenta din cuvant
            else if (incomingChar == currentWord[currentIndex]) {
                currentIndex++; 
                Serial.print(incomingChar); 
                if (currentIndex == currentWord.length()) {
                    Serial.println("\nCorrect!");
                    setActiveColor();
                    correctWordsCount++;
                    displayRandomWord(); 
                }
            } 
            else {
                setErrorColor();  
                Serial.print(incomingChar);
                currentIndex++;  
            }
        }
    }
}

void setup() {
    Serial.begin(9600);
    setupButtons();
    setIdleColor();
    randomSeed(analogRead(0));
}

void loop() {
    handleStartButton();
    handleDifficultyButton();
    updateGame();
}