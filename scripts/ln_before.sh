# 传入目录 如 5_xxxx
# 会前一目录 如 4_xxxx 的 .c 和 .h 文件夹 都 软链接 到 传入目录  
# 对于前一目录的 软链接 .c .h 文件夹 会找到其真实位置 再软链接
# 传入目录不存在则创建

cd ../code
mkdir -p "$1"
before_index=$(($(echo "$1" | perl -pe 's/^(.*?)_.*$/\1/') - 1))
before_dir=$(ls | grep "^${before_index}_")
before_files=$((ls "$before_dir"/*.cpp "$before_dir"/*.h && 
                find "$before_dir" -mindepth 1 -maxdepth 1 -type d &&
                find "$before_dir" -mindepth 1 -maxdepth 1 -type l -xtype d) |
                xargs -n 1 realpath)
echo "$before_files" | xargs -I {} bash -c "ln -fs {} "$1""  
