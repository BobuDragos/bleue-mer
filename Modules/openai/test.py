import sys
from openai import OpenAI

# Initialize the OpenAI client



# completion = client.chat.completions.create(
#   model="gpt-3.5-turbo",
#   messages=[
#     {"role": "system", "content": "You are a poetic assistant, skilled in explaining complex programming concepts with creative flair."},
#     {"role": "user", "content": "Compose a poem that explains the concept of recursion in programming."}
#   ]
# )

# print(completion.choices[0].message)




def get_chatgpt_response(message):
    completion = client.chat.completions.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": "you are a module inside a game-engine and represent the ai." },
            {"role": "system", "content": "You have to make fun of the player for not being able to defeat you."},
            {"role": "system", "content": "YOU MUST ANSWER WITH ONE SENTANCE ONLY"},
            {"role": "system", "content": "The following message will tell you which game you are playing and sometimes also the game state. (make sure to aknowledge the last played move and especially when there is a draw or a win):"},
            {"role": "user", "content": message}
        ]
    )
    return completion.choices[0].message.content

def main():
    if len(sys.argv) != 2:
        print("Usage: python chatgpt_script.py '<message>'")
        return
    
    message = sys.argv[1]
    response = get_chatgpt_response(message)
    response = response
    print(response)

if __name__ == "__main__":
    main()
