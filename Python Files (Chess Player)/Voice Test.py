import speech_recognition as sr

def getboard():
    """ gets a text string from the board """
    while True:
        r = sr.Recognizer()
        with sr.Microphone() as source:
            print("Say something!")
            btxt = r.listen(source)
        try:
            print "You said: " + r.recognize_google(btxt)
        except sr.UnknownValueError:
                print("Google Speech Recognition could not understand audio")
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service; {0}".format(e))
            x = r.recognize_google(btxt)
            y = here(20)
            if y == 1:
                break
    return x

def here(x):
    if x > 10:
        y = 1
    else:
        y = 0
    return y

getboard()