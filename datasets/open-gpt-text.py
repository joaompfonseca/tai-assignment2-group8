import json
import os
import pandas as pd
import numpy as np
import os

os.makedirs("out/open-gpt", exist_ok=True)
os.makedirs("out/open-gpt/train", exist_ok=True)
os.makedirs("out/open-gpt/val", exist_ok=True)

os.makedirs("out/open-gpt/train/0", exist_ok=True)
os.makedirs("out/open-gpt/train/1", exist_ok=True)

os.makedirs("out/open-gpt/val/0", exist_ok=True)
os.makedirs("out/open-gpt/val/1", exist_ok=True)

openweb_lst = []
chatgpt_lst = []

# Open Web Text
for i in range(10):
    if i in {7, 8}: continue
    with open(f"raw/open-gpt-text/openweb/urlsf_subset{i:02}.jsonl") as f:
        lines_raw = f.readlines()
        lines_json = [json.loads(line) for line in lines_raw]
        lines_text = [line["text"].replace("\n", " ") for line in lines_json]
        openweb_lst.extend(lines_text)

# ChatGPT Text
for i in range(10):
    if i in {7, 8}: continue
    with open(f"raw/open-gpt-text/chatgpt/urlsf_subset{i:02}.jsonl") as f:
        lines_raw = f.readlines()
        lines_json = [json.loads(line) for line in lines_raw]
        lines_text = [line["text"].replace("\n", " ") for line in lines_json]
        chatgpt_lst.extend(lines_text)

openweb_df = pd.DataFrame({"text": openweb_lst, "label": 0})
chatgpt_df = pd.DataFrame({"text": chatgpt_lst, "label": 1})

min_samples = min(openweb_df.shape[0], chatgpt_df.shape[0])
openweb_df = openweb_df.iloc[:min_samples]

for type, data in {"0": openweb_df, "1": chatgpt_df}.items():
    # data["text"] = data["text"].str.lower()
    data["text"] = data["text"].str.replace("\n", " ")

    train_size = int(0.8 * min_samples)
    train_df, test_df = data.iloc[:train_size], data.iloc[train_size:]
    np.savetxt(f"out/open-gpt/test{type}.txt", test_df["text"].values, fmt="%s")

    # create kfold splits
    splits = np.array_split(train_df["text"].values, 10)

    # iterate over splits, choose 1 split for validation, rest for training
    for i, split in enumerate(splits):
        train_folds = np.concatenate([splits[j] for j in range(10) if j != i])
        np.savetxt(f"out/open-gpt/train/{type}/train{i}.txt", train_folds, fmt="%s")
        np.savetxt(f"out/open-gpt/val/{type}/val{i}.txt", split, fmt="%s")
