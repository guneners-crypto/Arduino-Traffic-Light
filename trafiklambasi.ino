#define trigPin 9
#define echoPin 10

#define redLed 2
#define yellowLed 3
#define greenLed 4

long duration;
int distance;
int vehicleCount;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(greenLed, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    vehicleCount = detectVehicle();

    int greenTime;

    if(vehicleCount >= 3)
    {
        greenTime = 10000;
    }
    else
    {
        greenTime = 5000;
    }

    sendData(vehicleCount, greenTime);

    trafficLights(greenTime);
}

int detectVehicle()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 30000);

    if(duration == 0)
    {
        safeMode();
        return 0;
    }

    distance = duration * 0.034 / 2;

    if(distance > 2 && distance < 15)
    {
        return 3;
    }

    return 1;
}

void trafficLights(int greenTime)
{
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);

    delay(3000);

    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);

    delay(1000);

    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);

    delay(greenTime);

    digitalWrite(greenLed, LOW);
}

void sendData(int vehicleCount, int greenTime)
{
    Serial.print(vehicleCount);
    Serial.print(",");
    Serial.println(greenTime);
}

void safeMode()
{
    while(true)
    {
        digitalWrite(yellowLed, HIGH);
        delay(500);

        digitalWrite(yellowLed, LOW);
        delay(500);
    }
}
