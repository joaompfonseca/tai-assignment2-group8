import pandas as pd
import os

if __name__ == "__main__":

    wiki_intro_lst = []
    gene_intro_lst = []

    df = pd.read_parquet("raw/gpt-wiki-intro.parquet")

    for row in df.itertuples():
        wiki_intro = row.wiki_intro
        gene_intro = row.generated_intro

        # Remove line breaks
        wiki_intro = wiki_intro.replace("\n", " ")
        gene_intro = gene_intro.replace("\n", " ")

        wiki_intro_lst.append(wiki_intro)
        gene_intro_lst.append(gene_intro)

    # Save to separate files
    if not os.path.exists("out"):
        os.makedirs("out")

    with open(f"out/wiki_intro.txt", "w") as f:
        f.write("\n".join(wiki_intro_lst))
    with open(f"out/gene_intro.txt", "w") as f:
        f.write("\n".join(gene_intro_lst))
