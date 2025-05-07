import streamlit as st
from nltk.chat.util import Chat, reflections
#pip install streamlit nltk

#import nltk
#nltk.download('punkt')

#streamlit run your_script_name.py


# --- Menus and Prices ---
menu = {
    "beverages": ['Espresso', 'Cappuccino', 'Green Tea', 'Cold Coffee'],
    "snacks": ['Veg Sandwich', 'Cheese Garlic Bread', 'French Fries'],
    "desserts": ['Chocolate Brownie', 'Ice Cream Sundae', 'Muffin']
}

prices = {
    'Espresso': 120, 'Cappuccino': 150, 'Green Tea': 100, 'Cold Coffee': 140,
    'Veg Sandwich': 90, 'Cheese Garlic Bread': 110, 'French Fries': 100,
    'Chocolate Brownie': 130, 'Ice Cream Sundae': 160, 'Muffin': 90
}

# --- NLTK Pattern Chatbot for small talk/help ---
pairs = [
    (r'hi|hello|hey', ['Hey there! Welcome to CaféBot ☕']),
    (r'(.*)location(.*)', ['We are at FC Road, Pune!']),
    (r'(.*)hours|timing(.*)', ['We are open from 9 AM to 11 PM daily.']),
    (r'(.*)bye|exit', ['Goodbye! Have a great day 😊']),
    (r'(.*)menu|display menu', ['Here’s the full menu with prices:\n' +
                               "\n*Beverages*\n" + '\n'.join([f"{item} - ₹{prices[item]}" for item in menu['beverages']]) + 
                               "\n\n*Snacks*\n" + '\n'.join([f"{item} - ₹{prices[item]}" for item in menu['snacks']]) + 
                               "\n\n*Desserts*\n" + '\n'.join([f"{item} - ₹{prices[item]}" for item in menu['desserts']]) + 
                               "\n\nTo place an order, type *'start order'*"]),
    (r'(.*)thank(.*)', ['You’re welcome!'])
]
chat = Chat(pairs, reflections)

# --- State Setup ---
session = st.session_state
if "order_mode" not in session:
    session.order_mode = False
    session.step = 0
    session.category = ""
    session.cart = []
    session.chat_history = []
    session.current_item = None  # Track the item being ordered

# --- Helpers ---
def get_menu_string(cat):
    return '\n- ' + '\n- '.join([f"{item} - ₹{prices[item]}" for item in menu[cat]])

def add_to_cart(item, quantity):
    session.cart.append({"item": item, "quantity": quantity})

def remove_from_cart(item):
    session.cart = [x for x in session.cart if x["item"] != item]

def get_cart_string():
    if not session.cart:
        return "No items yet."
    summary = ""
    total = 0
    for i, entry in enumerate(session.cart, 1):
        item = entry["item"]
        quantity = entry["quantity"]
        price = prices[item]
        item_total = price * quantity
        total += item_total
        summary += f"{i}. {item} x{quantity} – ₹{price} x {quantity} = ₹{item_total}\n"
    summary += f"\n**Total: ₹{total}**"
    return summary

# --- Step Logic ---
def handle_order(message):
    message = message.lower().strip()

    # Step 0: Ask for category
    if session.step == 0:
        if message not in menu:
            return "Please choose a valid category: *beverages*, *snacks*, or *desserts*."
        session.category = message
        session.step = 1
        return f"You selected *{message.title()}*. Here's the menu:\n{get_menu_string(message)}\n\nWhat would you like to add?"

    # Step 1: Input item name
    elif session.step == 1:
        item = message.title()
        if item not in [i.title() for i in menu[session.category]]:
            return f"Sorry, we don't have *{item}* in {session.category.title()}. Please pick from the menu."
        
        session.current_item = item  # Store the selected item
        session.step = 2
        return f"Got it! How many *{item}* would you like? (Enter quantity)"

    # Step 2: Input quantity
    elif session.step == 2:
        try:
            quantity = int(message)
            if quantity <= 0:
                return "Please enter a positive number for quantity."
            
            add_to_cart(session.current_item, quantity)
            session.step = 3
            return f"✅ *{session.current_item} x{quantity}* added to your order! Would you like to add more items? (yes/no)"
        except ValueError:
            return "Please enter a valid number for quantity."

    # Step 3: Decide next step
    elif session.step == 3:
        if "yes" in message:
            session.step = 0
            return "Alright! What category would you like next: *beverages*, *snacks*, or *desserts*?"
        elif "no" in message:
            cart_summary = get_cart_string()
            session.order_mode = False
            session.step = 0
            session.category = ""
            session.current_item = None
            return f"🧾 Here’s your final order:\n\n{cart_summary}\n\nThank you for ordering from CaféBot ☕!"
        else:
            return "Please reply with *yes* to add more or *no* to complete your order."

# --- Streamlit UI ---
st.set_page_config(page_title="CaféBot – Multi Item", layout="centered")
st.title("☕ CaféBot – Your Friendly Café Assistant")
st.markdown("Ask about our menu, place orders, or just say hi! Type *'start order'* to begin your order.")

# Initialize bot_reply to avoid undefined variable error
bot_reply = ""

# Chat interface with a cool theme
user_input = st.chat_input("Say something...")

if user_input:
    msg = user_input.strip()
    
    if session.order_mode:
        bot_reply = handle_order(msg)
    elif "start order" in msg.lower():
        session.order_mode = True
        session.cart = []
        session.step = 0
        bot_reply = "Great! Let's get started. Would you like to begin with *beverages*, *snacks*, or *desserts*?"
    else:
        bot_reply = chat.respond(msg)
        if not bot_reply:
            bot_reply = "I'm here to help you order. Try typing 'start order' to begin or ask about our menu."

    session.chat_history.append(("You", msg))
    session.chat_history.append(("CaféBot", bot_reply))

# --- Show Chat ---
for sender, message in session.chat_history:
    with st.chat_message("user" if sender == "You" else "assistant"):
        st.markdown(message)

# --- End of Order ---
if "no" in bot_reply and "final order" in bot_reply:
    order_summary = get_cart_string()
    st.markdown(order_summary)