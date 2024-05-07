import pandas as pd
from sklearn.model_selection import train_test_split, KFold
import os

os.makedirs("out/wiki", exist_ok=True)
os.makedirs("out/wiki/train", exist_ok=True)

df = pd.read_parquet("raw/gpt-wiki-intro.parquet")
num_samples = df.shape[0]

texts = pd.concat([df["wiki_intro"], df["generated_intro"]], axis=0)
df = pd.DataFrame({"text": texts, "label": [0]*num_samples + [1]*num_samples})
df["text"] = df["text"].str.lower()

train_df, test_df = train_test_split(df, test_size=0.2, random_state=42)
test_df.to_csv("out/wiki/test.csv", index=False)

# create kfold splits
kf = KFold(n_splits=10, shuffle=True, random_state=42)

for i, (train_idx, val_idx) in enumerate(kf.split(train_df)):
    train_df.iloc[val_idx].to_csv(f"out/wiki/train/fold_{i}.csv", index=False)
