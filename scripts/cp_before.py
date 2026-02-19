### 复制 获取到当前笔记本为止的所有 %%file 编写的最新代码

import nbformat
import os
import sys

def process_notebook(path):
    nb = nbformat.read(path, as_version=4)

    for cell in nb.cells:
        if cell.cell_type != "code":
            continue

        lines = cell.source.splitlines()
        if not lines:
            continue

        first_line = lines[0].strip()

        if first_line.startswith("%%file"):
            # 解析路径
            target_path = first_line.split(" ", 1)[1].strip()

            content = "\n".join(lines[1:])

            # 创建目录
            os.makedirs(os.path.dirname(target_path), exist_ok=True)

            # 写入文件
            with open(target_path, "w", encoding="utf-8") as f:
                f.write(content)

def get_all_notebook(current):
    dir = os.path.dirname(current)
    filename = os.path.basename(current)
    
    lst = []

    getIndex = lambda filename: int(filename.split('_')[0])

    for file in os.listdir(dir):
        if not file.endswith('.ipynb'):
            continue

        lst.append(file)

    lst.sort(key=lambda file: getIndex(file)) 

    pos = lst.index(filename)

    return list(map(lambda filename: os.path.join(dir, filename), lst[:pos + 1]))

if __name__ == "__main__":
    for file in get_all_notebook(sys.argv[1]):
        process_notebook(file)
