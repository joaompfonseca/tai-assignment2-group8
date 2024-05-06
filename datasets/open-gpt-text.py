import json
import os

if __name__ == "__main__":

    openweb_lst = []
    chatgpt_lst = []

    # Open Web Text
    for i in [0, 1, 2, 3, 4, 5, 6, 9]:
        with open(f"raw/open-gpt-text/openweb/urlsf_subset{i:02}.jsonl") as f:
            lines_raw = f.readlines()
            lines_json = [json.loads(line) for line in lines_raw]
            lines_text = [line["text"].replace("\n", " ") for line in lines_json]
            openweb_lst.extend(lines_text)

    # ChatGPT Text
    for i in [0, 1, 2, 3, 4, 5, 6, 9]:
        with open(f"raw/open-gpt-text/chatgpt/urlsf_subset{i:02}.jsonl") as f:
            lines_raw = f.readlines()
            lines_json = [json.loads(line) for line in lines_raw]
            lines_text = [line["text"].replace("\n", " ") for line in lines_json]
            chatgpt_lst.extend(lines_text)

    # Save to separate files
    if not os.path.exists("out"):
        os.makedirs("out")

    with open(f"out/open_web.txt", "w") as f:
        f.write("\n".join(openweb_lst))
    with open(f"out/open_gpt.txt", "w") as f:
        f.write("\n".join(chatgpt_lst))

