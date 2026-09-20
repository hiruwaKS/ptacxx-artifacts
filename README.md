# PTACXX-ARTIFACTS

> [see PTACXX](https://github.com/hiruwaKS/ptacxx)

- artifact
    - The name must be kebab-case (<type><date>-<name>)
    - The name must be unique
    - It may reference other artifacts.
        - Different artifacts document their own information; avoid duplication.
    - categories
        - experiment (start with e)
        - dataset (start with d)
- `report.md`
    - A report is the proof of qualification for an artifact
    - **Purpose**
    - **Data Generation**
        - How the data is generated
    - **Data Result**
        - mainly some basic statistics
    - **Conclusion** (only for `experiment` artifacts)
        - Whether the hypothesis holds, what the metrics are, how it compares to the baseline, whether it supports a certain claim
    - **Usage** (only for `dataset` artifacts)
        - Field meanings, format, license, download/loading method, preprocessing suggestions, usage limitations
    - **Other notes**
        - Record pitfalls to avoid
        - Useful things
        - Interesting things
        - TODO
        - Related work
- `data`
    - small files
        - small statistics
        - illustration
    - blob
        - `reproducible.md`: contain commands to reproduce the data and private information
        - large table (e.g. csv)
        - bitcode/binary file
        - **will not be uploaded**
