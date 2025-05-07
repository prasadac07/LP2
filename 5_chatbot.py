import spacy
import nltk
from nltk.chat.util import Chat, reflections

# Load the spaCy language model
nlp = spacy.load('en_core_web_sm')

# Define the greeting and response rules
pairs = [
    (r'hi|hello|hey', ['Hello! How can I help you today?', 'Hi! How can I assist you today?']),
    (r'what is your name?', ['I am a friendly chatbot. You can call me ChatBot.']),
    (r'how are you?', ['I am doing great! How about you?', 'I am fine, thank you for asking!']),
    (r'what can you do?', ['I can assist you with answering questions, providing recommendations, and guiding you.']),
    (r'bye|goodbye', ['Goodbye! Have a great day!', 'See you later! Take care.']),
]

# Create a simple chatbot
chatbot = Chat(pairs, reflections)

def process_input(user_input):
    # Tokenize and process input using spaCy
    doc = nlp(user_input)
    response = chatbot.respond(user_input)
    if response:
        return response
    else:
        return "Sorry, I didn't quite understand that. Can you please rephrase?"

# A simple interactive chat loop
def start_chat():
    print("Welcome to the customer support chatbot! Type 'bye' to end the conversation.")
    while True:
        user_input = input("You: ")
        if user_input.lower() == 'bye':
            print("ChatBot: Goodbye!")
            break
        response = process_input(user_input)
        print(f"ChatBot: {response}")

# Start the chatbot
start_chat()
