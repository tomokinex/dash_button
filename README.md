# 導入方法
1. amazon dash buttonの設定をする
1. amazon dash buttonのMACアドレスを調べ, address.txtに記入する
1. 使いたいインターフェースごとに設定をして, ソースコードにURLを記入する
1. コンパイルする
1. 実行する
# amazon dash buttonのMACアドレスの調べ方
- wire shark等のパケットキャプチャソフトで調べる
- arp_rev.cで調べる(以下, 実行方法)

```:shell
make arp
sudo ./arp
```
# makeのオプション
makeのターゲット指定を変えることで, buttonが押されたときの挙動を変えることができる

```:shell
make line
```
 line以外にはstack, voice等がターゲットとして記入してある 　
 allはsample.cpp  

# buttonを押したときの挙動
makeのターゲットにした各々のファイルについて, buttonが押されたときの挙動を設定できる  
## line.cpp, voice.cppの場合
IFTTTの[webhooks](https://ifttt.com/maker_webhooks)というサービスを用いる  
POSTしたHTTP requestをhookして, 別のアプリに通知を送ることができる  
IFTTTに登録すると, 個人用のtokenが発行されるので, サンプルのcurl scriptの内容をそのままコピーする  

## slack.cppの場合
[Incoming Webhook](https://api.slack.com/incoming-webhooks)というslackのインテグレーションを用いる  
これも, POSTしたHTTP requestをhookして, slackに通知を送ることができる  
Incoming Webhookを導入して表示されるサンプルのcurl scriptを参考に記入する  

# 参考
http://jis.hatenablog.com/entry/2013/09/20/143655