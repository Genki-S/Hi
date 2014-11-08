json.array!(@pn_jp_words) do |pn_jp_word|
  json.extract! pn_jp_word, :id, :word, :kana, :pos, :value
  json.url pn_jp_word_url(pn_jp_word, format: :json)
end
