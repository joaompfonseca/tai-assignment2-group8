import json
import os
import pandas as pd
from sklearn.model_selection import train_test_split, KFold
import os

os.makedirs("out/open-gpt", exist_ok=True)
os.makedirs("out/open-gpt/train", exist_ok=True)

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
openweb_df = openweb_df.sample(n=min_samples, random_state=42)

df = pd.concat([openweb_df, chatgpt_df], axis=0)
df["text"] = df["text"].str.lower()

train_df, test_df = train_test_split(df, test_size=0.2, random_state=42)
test_df.to_csv("out/open-gpt/test.csv", index=False)

# create kfold splits
kf = KFold(n_splits=10, shuffle=True, random_state=42)

for i, (train_idx, val_idx) in enumerate(kf.split(train_df)):
    train_df.iloc[val_idx].to_csv(f"out/open-gpt/train/fold_{i}.csv", index=False)
