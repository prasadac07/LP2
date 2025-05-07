# Define the Book class
class Book:
    def __init__(self, title, author, genre, keywords, availability):
        self.title = title
        self.author = author
        self.genre = genre
        self.keywords = keywords
        self.availability = availability

    def __repr__(self):
        return f"{self.title} by {self.author} ({self.genre})"

# Define the User class
class User:
    def __init__(self, name, project_topic, domain, difficulty_level):
        self.name = name
        self.project_topic = project_topic
        self.domain = domain
        self.difficulty_level = difficulty_level

# Function to recommend books based on user preferences
def recommend_books(user, books):
    recommendations = []
    
    # Filter books based on the domain and availability
    for book in books:
        if user.domain.lower() in book.genre.lower() and book.availability == "Available":
            match_score = 0
            
            # Match project topic with book keywords
            for keyword in book.keywords:
                if user.project_topic.lower() in keyword.lower():
                    match_score += 1
            
            # Adjust match score based on difficulty level
            if user.difficulty_level.lower() == "beginner" and match_score > 1:
                match_score += 1
            elif user.difficulty_level.lower() == "expert" and match_score > 2:
                match_score += 1
            
            # Add book to recommendations with score
            recommendations.append((book, match_score))
    
    # Sort books based on match score (higher score = better match)
    recommendations.sort(key=lambda x: x[1], reverse=True)
    
    # Return top 3 recommendations (or fewer if there are not enough matches)
    return [book[0] for book in recommendations[:3]]

# Sample Book Data (predefined knowledge base)
books = [
    Book("AI for All", "John Doe", "Computer Science", ["Machine Learning", "AI", "Introduction"], "Available"),
    Book("Data Science Mastery", "Jane Smith", "Computer Science", ["Data Science", "Machine Learning", "Intermediate"], "Available"),
    Book("Ethics in AI", "Mark Johnson", "Computer Science", ["AI Ethics", "Responsibility", "Philosophy"], "Checked Out"),
    Book("Business Intelligence", "Emma White", "Business", ["BI", "Data Analytics", "Business Case Studies"], "Available"),
    Book("Advanced Machine Learning", "Alice Green", "Computer Science", ["Machine Learning", "Deep Learning", "Advanced"], "Available"),
    Book("AI and Society", "Bob Blue", "Social Sciences", ["AI", "Ethics", "Social Impact"], "Available")
]

# Function to take user input for their project work
def take_user_input():
    print("Welcome to the Library Expert System!")
    
    name = input("Enter your name: ")
    project_topic = input("Enter your project topic (e.g., Machine Learning, AI Ethics, etc.): ")
    domain = input("Enter the domain of your project (e.g., Computer Science, Business, Social Sciences): ")
    difficulty_level = input("Enter the difficulty level of your project (Beginner, Intermediate, Expert): ")
    
    return User(name, project_topic, domain, difficulty_level)

# Main code to interact with the system
if __name__ == "__main__":
    # Take user inputs
    user = take_user_input()

    # Get Book Recommendations for the User
    recommended_books = recommend_books(user, books)

    # Display Recommended Books
    print(f"\nRecommended Books for {user.name} (Topic: {user.project_topic}, Difficulty: {user.difficulty_level}):")
    if recommended_books:
        for book in recommended_books:
            print(f"- {book}")
    else:
        print("No books found that match your requirements.")
