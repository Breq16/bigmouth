from pydub import AudioSegment

clip = AudioSegment.from_mp3("track002.mp3")

length = len(clip)
rms = clip.rms
slices = []

for i in range(0, len(clip), 10):
    slices.append(clip[i:i+10])

# loudnesses = [(slice.max / slice.max_possible_amplitude) for slice in slices]

# Normalize to RMS
loudnesses = [slice.rms / rms for slice in slices]

# Adjust to 0-255 scale for Arduino
loudnesses = [min(int(loudness*128), 255) for loudness in loudnesses]

with open("loudness.h", "w") as header:
    header.write("# pragma once\n")
    header.write("const uint8_t loudness[] PROGMEM = {")
    header.write(", ".join(str(ampl) for ampl in loudnesses))
    header.write("};\n")
