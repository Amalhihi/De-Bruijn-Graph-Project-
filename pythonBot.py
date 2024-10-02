TOKEN = '6337759216:AAHPFfGu7NJw7VRBhCypm2F1WfXBnB9-5n4'
userName = '@deBroynProjectBot'
from telegram import Update
from telegram.ext import Application, CommandHandler, MessageHandler, filters, ContextTypes

import re
# import the module
def contains_only_numbers_or_spaces(text):
    # Use a regular expression to check if the string contains only numbers or spaces
    return bool(re.match('^[0-9\s]+$', text))

def split_message(message, max_length=4096):
    # Check if the message exceeds the maximum length
    if len(message) <= max_length:
        return [message]

    # Calculate the number of parts needed
    num_parts = (len(message) + max_length - 1) // max_length

    # Split the message into parts
    message_parts = [message[i * max_length:(i + 1) * max_length] for i in range(num_parts)]

    return message_parts
def split_message_by_length_and_blank_lines(message, max_length=4096, max_consecutive_blank_lines=2):
    # Split the message into paragraphs based on consecutive blank lines
    paragraphs = [p.strip() for p in message.split('\n\n')]

    # Initialize variables
    current_part = ''
    message_parts = []

    for paragraph in paragraphs:
        # Check if adding the current paragraph exceeds the maximum length
        if len(current_part) + len(paragraph) + 2 <= max_length:
            # Add the paragraph to the current part with a newline separator
            current_part += paragraph + '\n\n'
        else:
            # Save the current part and start a new one with the current paragraph
            message_parts.append(current_part.strip())
            current_part = paragraph + '\n\n'

    # Add the last part if it's not empty
    if current_part.strip():
        message_parts.append(current_part.strip())

    return message_parts
import subprocess

print("starting bot")
app = Application.builder().token(TOKEN).build()
# Path to the executable file
exe_path = "C:/Users/aviel/CLionProjects/DeBroynEnd/a.exe"

# Input data to be passed to the executable
input_data = ''

#popen=subprocess.Popen(exe_path,text=True)




async def start_command(update, contex):
    await update.message.reply_text("hello Tovi. this is a bot that simulates part 2 of our project")
    await update.message.reply_text("write all the necessary input, in the format of [polynomial degree] [polynomial index] [block sizes] [window size]")







async def part2_command(update, contex):
    await update.message.reply_text("write all the necessary input, in the format of [polynomial degree] [polynomial index] [block sizes] [window size]")


def handle_response(text: str):
    global popen
    global input_data
    if not contains_only_numbers_or_spaces(text):
        return 'please input only the input numbers'
    base_input = input_data
    input_data += text

    result = subprocess.run([exe_path], input=input_data, text=True, capture_output=True, check=True)
    input_data = base_input
    return result.stdout


async def handle_message(update, contex):
    text = update.message.text
    print(f'User ({update.message.chat.id}) sands : {text}')
    response = handle_response(text)
    responses=split_message(response)
    for res in responses:
        await update.message.reply_text(res)


# commands
app.add_handler(CommandHandler('start', start_command))
app.add_handler(CommandHandler('part2', part2_command))
# messages
app.add_handler(MessageHandler(filters.TEXT, handle_message))

# polling
app.run_polling(poll_interval=3)
