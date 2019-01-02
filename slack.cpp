#include <stdlib.h>
void execute(){
    system("curl -X POST --data-urlencode 'payload={\"username\": \"webhookbot\", \"text\": \"これは webhookbot という名のボットから投稿されています。\", \"icon_emoji\": \":ghost:\"}'https://hooks.slack.com/services/{$url}}");
}