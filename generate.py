import json

with open("recorded.json") as file:
    actions = json.load(file)

code = []

action_lines = {
    "head": "  fish.head();",
    "tail": "  fish.tail();",
    "rest": "  fish.rest();",
    "mouthOpen": "  fish.setMouth(1);",
    "mouthClosed": "  fish.setMouth(0);"
}

for timestamp, action in actions.items():
    millis = int(float(timestamp)*1000)
    code.append(f"  delay({millis});")
    code.append(action_lines[action])

generated = "\n".join(code)

with open("routine.ino", "w") as file:
    file.write("void routine() {\n")
    file.write(generated)
    file.write("\n}\n")
