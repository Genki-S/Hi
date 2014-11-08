class CreatePnJpWords < ActiveRecord::Migration
  def change
    create_table :pn_jp_words do |t|
      t.string :word
      t.string :kana
      t.string :pos
      t.float :value

      t.timestamps
    end
  end
end
