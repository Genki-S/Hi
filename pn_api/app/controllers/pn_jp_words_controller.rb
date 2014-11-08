class PnJpWordsController < ApplicationController
  before_action :set_pn_jp_word, only: [:show, :edit, :update, :destroy]

  # GET /pn_jp_words
  # GET /pn_jp_words.json
  def index
    @pn_jp_words = PnJpWord.all
  end

  # GET /pn_jp_words/1
  # GET /pn_jp_words/1.json
  def show
  end

  # GET /pn_jp_words/new
  def new
    @pn_jp_word = PnJpWord.new
  end

  # GET /pn_jp_words/1/edit
  def edit
  end

  # POST /pn_jp_words
  # POST /pn_jp_words.json
  def create
    @pn_jp_word = PnJpWord.new(pn_jp_word_params)

    respond_to do |format|
      if @pn_jp_word.save
        format.html { redirect_to @pn_jp_word, notice: 'Pn jp word was successfully created.' }
        format.json { render :show, status: :created, location: @pn_jp_word }
      else
        format.html { render :new }
        format.json { render json: @pn_jp_word.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /pn_jp_words/1
  # PATCH/PUT /pn_jp_words/1.json
  def update
    respond_to do |format|
      if @pn_jp_word.update(pn_jp_word_params)
        format.html { redirect_to @pn_jp_word, notice: 'Pn jp word was successfully updated.' }
        format.json { render :show, status: :ok, location: @pn_jp_word }
      else
        format.html { render :edit }
        format.json { render json: @pn_jp_word.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /pn_jp_words/1
  # DELETE /pn_jp_words/1.json
  def destroy
    @pn_jp_word.destroy
    respond_to do |format|
      format.html { redirect_to pn_jp_words_url, notice: 'Pn jp word was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_pn_jp_word
      @pn_jp_word = PnJpWord.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def pn_jp_word_params
      params.require(:pn_jp_word).permit(:word, :kana, :pos, :value)
    end
end
