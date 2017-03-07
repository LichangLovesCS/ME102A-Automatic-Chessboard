# initiate chessboard
import subprocess

import speech_recognition as sr
from ChessBoard import ChessBoard

r = sr.Recognizer()

maxchess = ChessBoard()
# ser = serial.Serial('COM8', 9600)

# initiate stockfish chess engine

engine = subprocess.Popen(
    'stockfish 7 x64.exe',
    universal_newlines=True,
    stdin=subprocess.PIPE,
    stdout=subprocess.PIPE, )


def get():
    # using the 'isready' command (engine has to answer 'readyok')
    # to indicate current last line of stdout
    stx = ""
    engine.stdin.write('isready\n')
    print('\nengine:')
    while True:
        text = engine.stdout.readline().strip()
        if text == 'readyok':
            break
        if text != '':
            print('\t' + text)
        if text[0:8] == 'bestmove':
            return text


def sget():
    # using the 'isready' command (engine has to answer 'readyok')
    # to indicate current last line of stdout
    stx = ""
    engine.stdin.write('isready\n')
    print('\nengine:')
    while True:
        text = engine.stdout.readline().strip()
        # if text == 'readyok':
        #   break
        if text != '':
            print('\t' + text)
        if text[0:8] == 'bestmove':
            mtext = text
            return mtext


def getboard():
    """ gets a text string from the board """
    while True:
        r = sr.Recognizer()
        y = 0
        with sr.Microphone() as source:
            print("Say something!")
            btxt = r.listen(source)
        try:
            print "You said: " + r.recognize_google(btxt)
            x, y = voice2str(r.recognize_google(btxt))
        except sr.UnknownValueError:
            continue
        except KeyError:
            continue
        if y == 4:
            break
        else:
            print("Sorry, I did not get that")
    # ser.write(x[-4:])
    return x


def voice2str(str):
    strlist = str.split()
    x = "m"
    y = 0
    for i in strlist:
        print i
        i = i.lower()
        if i == "alpha" or i == "a":
            x += "a"
            y += 1
        elif i == "bravo" or i == "brother" or i == "b":
            x += "b"
            y += 1
        elif i == "charlie":
            x += "c"
            y += 1
        elif i == "delta":
            x += "d"
            y += 1
        elif i == "echo":
            x += "e"
            y += 1
        elif i == "foxtrot":
            x += "f"
            y += 1
        elif i == "gulf":
            x += "g"
            y += 1
        elif i == "hotel":
            x += "h"
            y += 1
        if i == "one" or i == "won" or i == "1":
            x += "1"
            y += 1
        elif i == "to" or i == "too" or i == "2" or i == "two":
            x += "2"
            y += 1
        elif i == "three" or i == "3":
            x += "3"
            y += 1
        elif i == "four" or i == "for" or i == "4" or i == "floor":
            x += "4"
            y += 1
        elif i == "five" or i == "5":
            x += "5"
            y += 1
        elif i == "six" or i == "6":
            x += "6"
            y += 1
        elif i == "seven" or i == "7":
            x += "7"
            y += 1
        elif i == "eight" or i == "ate" or i == "8":
            x += "8"
            y += 1
    print x, y
    return x, y


def sendboard(stxt):
    """ sends a text string to the board """
    print("\n send to board: " + stxt)


def newgame():
    get()
    put('uci')
    get()
    put('setoption name Skill Level value ' + skill)
    get()
    put('setoption name Hash value 128')
    get()
    put('setoption name Best Book Move value true')
    get()
    put('setoption name OwnBook value true')
    get()
    put('uci')
    get()
    put('ucinewgame')
    maxchess.resetBoard()
    fmove = ""
    return fmove


def bmove(fmove):
    """ assume we get a command of the form ma1a2 from board"""
    fmove = fmove
    # Get a move from the board
    brdmove = bmessage[1:5].lower()
    # now validate move
    # if invalid, get reason & send back to board
    #  maxchess.addTextMove(move)
    if maxchess.addTextMove(brdmove) == False:
        etxt = "error" + str(maxchess.getReason()) + brdmove
        maxchess.printBoard()
        sendboard(etxt)
        return fmove

    # elif valid  make the move and send Fen to board

    else:
        maxchess.printBoard()
        # maxfen = maxchess.getFEN()
        # sendboard(maxfen)
        # remove line below when working
        raw_input(("\n\nPress the enter key to continue"))
        print("fmove")
        print(fmove)
        print("brdmove")
        print(brdmove)
        fmove = fmove + " " + brdmove

        cmove = "position startpos moves" + fmove
        print(cmove)

        #        if fmove == True :
        #                move = "position startpos moves "+move
        #        else:
        #               move ="position fen "+maxfen

        # put('ucinewgame')
        # get()


        put(cmove)
        # send move to engine & get engines move


        put("go movetime " + movetime)
        # time.sleep(6)
        # text = get()
        # put('stop')
        text = sget()
        print(text)
        smove = text[9:13]
        hint = text[21:25]
        if maxchess.addTextMove(smove) != True:
            stxt = "e" + str(maxchess.getReason()) + smove
            maxchess.printBoard()
            sendboard(stxt)

        else:
            temp = fmove
            fmove = temp + " " + smove
            stx = smove + hint
            sendboard(stx)
            maxchess.printBoard()
            # maxfen = maxchess.getFEN()
            print("computer move: " + smove)
            # ser.write(smove)
            return fmove


def put(command):
    print('\nyou:\n\t' + command)
    engine.stdin.write(command + '\n')


# assume new game
print("\n Chess Program \n")
skill = "10"
movetime = "6000"
fmove = newgame()
while True:

    # Get  message from board
    bmessage = getboard()
    # Message options   Move, Newgame, level, style
    code = bmessage[0]

    # decide which function to call based on first letter of txt
    fmove = fmove
    if code == 'm':
        fmove = bmove(fmove)
    elif code == 'n':
        newgame()
    elif code == 'l':
        level()
    elif code == 's':
        style()
    else:
        sendboard('error at option')
