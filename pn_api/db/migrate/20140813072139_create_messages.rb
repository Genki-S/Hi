class CreateMessages < ActiveRecord::Migration
  def change
    create_table :messages do |t|
      t.string :to_uid
      t.string :from_uid
      t.text :body
      t.text :raw_body
      t.float :pn_value
      t.datetime :opened_at
      t.datetime :sent_at

      t.timestamps
    end
  end
end
