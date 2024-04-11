import base64
from openai import OpenAI
import requests

# OpenAI API Key
api_key = "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"

# Function to encode the image
def encode_image(image_path):
  with open(image_path, "rb") as image_file:
    return base64.b64encode(image_file.read()).decode('utf-8')

# Path to your image
image_path = "../image/gptImage.png"

# Getting the base64 string
base64_image = encode_image(image_path)

headers = {
  "Content-Type": "application/json",
  "Authorization": f"Bearer {api_key}"
}

payload = {
  "model": "gpt-4-vision-preview",
  "messages": [
    {
      "role": "user",
      "content": [
        {
          "type": "text",
          "text": "What is the object in this image in one to five words?"
        },
        {
          "type": "image_url",
          "image_url": {
            "url": f"data:image/jpeg;base64,{base64_image}"
          }
        }
      ]
    }
  ],
  "max_tokens": 300
}

response = requests.post("https://api.openai.com/v1/chat/completions", headers=headers, json=payload)

api_response = response.json()
objectIdent = api_response['choices'][0]['message']['content']


#getting the definition of the object that was identified
client = OpenAI(api_key = api_key)

response = client.chat.completions.create(
  model="gpt-3.5-turbo",
  messages=[
    {"role": "user", "content": "Give the definition of" + objectIdent + "in 1 or 2 sententences. Respond using the format word defined: definition"}
  ]
)
print(response.choices[0].message.content)

  
