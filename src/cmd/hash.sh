# Tirado de https://github.com/kth-competitive-programming/kactl/
cpp -P -fpreprocessed $1 | tr -d '[:space:]'| md5sum |cut -c-6
